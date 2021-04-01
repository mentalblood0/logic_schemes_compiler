import json

standard_elements = ['NOT', 'AND', 'OR', 'INPUT', 'OUTPUT']

def getUniqueElements(description):
	result = {}
	for w in description['wires']:
		result[w['from']] = None
		result[w['to']] = None
	return result

def getElementsInputs(description):
	result = {}
	for w in description['wires']:
		element = w['to'].split('[')[0]
		if not (element in result):
			result[element] = {}
		input_index = w['to'][:-1].split('[')[-1]
		try:
			result[element][int(input_index)] = w['from']
		except ValueError:
			result[element][0] = w['from']
	return result

def defineFunction(description):
	result = ''
	unique_elements = getUniqueElements(description)
	inputs_by_element = getElementsInputs(description)

	inputs_number = len(list(filter(lambda e: e.split('_')[0] == 'INPUT', unique_elements)))
	outputs_number = len(list(filter(lambda e: e.split('_')[0] == 'OUTPUT', unique_elements)))

	macros_prefix = '__' + description['name'] + '__'
	inputs_string = ', '.join([f'{macros_prefix}INPUT_{n}' for n in range(1, inputs_number+1)])
	
	for e in inputs_by_element.keys():
		arguments_list = []
		for i in inputs_by_element[e].values():
			if i.split('_')[-2] == 'INPUT':
				arguments_list.append(f'{macros_prefix}{i}')
			elif '[' in i:
				i_without_index = i.split('[')[0]
				number_of_output_to_take = i[:-1].split('[')[-1]
				arguments_list.append(f"NTH_{number_of_output_to_take}({macros_prefix}{i_without_index}({inputs_string}))")
			else:
				number_of_output_to_take = 0
				arguments_list.append(f"{macros_prefix}{i}({inputs_string})")
		arguments = ', '.join(arguments_list)
		result += f"#define {macros_prefix}{e}({inputs_string}) {e.split('_')[0]}({arguments})\n"
	
	function_outputs_string = ', '.join([
		f'{macros_prefix}OUTPUT_{n}({inputs_string})'
		for n in range(1, outputs_number+1)
	])
	result += f"#define {description['name']}({inputs_string}) {function_outputs_string}"
	
	return result, outputs_number

def defineTestFunction(description):
	equalities_list = []
	for t in description['tests']:
		inputs_string = ', '.join(map(str, t['inputs']))
		for output_index in range(len(t['outputs'])):
			output = t['outputs'][output_index]
			equalities_list.append(f"(NTH_{output_index}({description['name']}({inputs_string})) == {output})")
	equalities = ' && '.join(equalities_list)
	result = f"#define test_{description['name']} ({equalities})"
	return result

def checkNoCycles(current_from, from_to, stack=[]):
	if current_from in stack:
		return False, stack + [current_from]

	if not (current_from in from_to):
		return True, None

	for _to in from_to[current_from]:
		c = checkNoCycles(_to, from_to, stack = stack + [current_from])
		if not c[0]:
			return False, c[1]

	return True, None

def checkFunctionNoCycles(description):
	from_to = {}
	for w in description['wires']:
		from_element = w['from'].split('[')[0]
		to_element = w['to'].split('[')[0]
		if not from_element in from_to:
			from_to[from_element] = []
		from_to[from_element].append(to_element)
	
	for initial_from in from_to.keys():
		c = checkNoCycles(initial_from, from_to)
		if not c[0]:
			return False, c[1]

	return True, None

def checkFunction(description, checks=[checkFunctionNoCycles]):
	for c in checks:
		c_result = c(description)
		if not c_result[0]:
			return False, {c.__name__: c_result[1]}
	return True, None

def compile(file_path):
	result = '''#include <stdio.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

'''
	program = None
	with open('example.json', 'r') as f:
		program = json.load(f)

	outputs_numbers = {}
	definitions = ''
	for description in program:
		check_result = checkFunction(description)
		if not check_result[0]:
			raise Exception(f'Function "{description["name"]}" not correct: {check_result[1]}')
		definition, outputs_number = defineFunction(description)
		test_function_definition = defineTestFunction(description)
		definitions += '\n\n' + definition + '\n' + test_function_definition
		outputs_numbers[description['name']] = outputs_number

	result += '''
#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_0(...) FIRST(__VA_ARGS__)
'''
	for i in range(1, max(outputs_numbers.values())):
		result += f'#define NTH_{i}(...) NTH_{i-1}(REST(__VA_ARGS__))\n'

	result += definitions
	result += '\n'
	result += '\n'
	result += f"""#define test__all {' && '.join([f'test_{d["name"]}' for d in program])}"""

	result += '\n'
	result += '\n'
	result += 'int main(void) {\n'
	result += '\tprintf("tests:\\n");\n'
	result += ''.join([f'\tprintf("\\t{d["name"]}: %s\\n", test_{d["name"]} ? "passed" : "failed");\n' for d in program])
	result += '\tprintf("%s\\n", test__all ? "All tests passed" : "Some tests not OK");\n'
	result += '\treturn 0;\n'
	result += '}'

	return result