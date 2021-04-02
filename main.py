import json

standard_elements_types_inputs_outputs = {
	'NOT': 		{'inputs': 1, 'outputs': 1},
	'AND': 		{'inputs': 2, 'outputs': 1},
	'OR': 		{'inputs': 2, 'outputs': 1},
	'INPUT': 	{'inputs': 0, 'outputs': 1},
	'OUTPUT': 	{'inputs': 1, 'outputs': 0}
}

def getElementType(element):
	return element.split('_')[0]

def getElementName(element_input_or_output):
	return element_input_or_output.split('[')[0]

def getElementsNumbers(description):
	result = {}
	for e in sum([[w['from'], w['to']] for w in description['wires']], []):
		element_name = getElementName(e)
		element_type = getElementType(e)
		if not element_type in result:
			result[element_type] = {}
		result[element_type][element_name] = None
	result = {key: len(value.keys()) for key, value in result.items()}
	return result

def getInputsOutputsNumbersForType(description):
	elements_numbers = getElementsNumbers(description)
	return {
		'inputs': 0 if not ('INPUT' in elements_numbers) else elements_numbers['INPUT'],
		'outputs': 0 if not ('OUTPUT' in elements_numbers) else elements_numbers['OUTPUT']
	}

def getInputsOutputsNumbersForInnerElements(description):
	result = {}
	for w in description['wires']:
		
		from_element = getElementName(w['from'])
		if not from_element in result:
			result[from_element] = {'inputs': 0, 'outputs': 0}
		result[from_element]['outputs'] += 1
		
		to_element = getElementName(w['to'])
		if not to_element in result:
			result[to_element] = {'inputs': 0, 'outputs': 0}
		result[to_element]['inputs'] += 1
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
			result[element][1] = w['from']
	return result



def defineFunction(name, description):
	result = ''
	inputs_by_element = getElementsInputs(description)

	elements_numbers = getElementsNumbers(description)
	inputs_number = elements_numbers['INPUT']
	outputs_number = elements_numbers['OUTPUT']

	macros_prefix = '__' + name + '__'
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
		for n in range(1, outputs_number + 1)
	])
	result += f"#define {name}({inputs_string}) {function_outputs_string}"
	
	return result, outputs_number

def defineTestFunction(name, description):
	equalities_list = []
	for t in description['tests']:
		inputs_string = ', '.join(map(str, t['inputs']))
		for output_index in range(len(t['outputs'])):
			output = t['outputs'][output_index]
			equalities_list.append(f"(NTH_{output_index + 1}({name}({inputs_string})) == {output})")
	equalities = ' && '.join(equalities_list)
	result = f"#define test_{name} ({equalities})"
	return result



def checkNoCycles(current_from, from_to, stack=[]):
	if current_from in stack:
		return False, f'Cycle: {stack + [current_from]}'

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
	
	inputs = [e for e in from_to if e.split('_')[0] == 'INPUT']
	for initial_from in inputs:
		c = checkNoCycles(initial_from, from_to)
		if not c[0]:
			return False, c[1]

	return True, None

def checkFunction(description, checks=[checkFunctionNoCycles]):
	for c in checks:
		c_result = c(description)
		if not c_result[0]:
			return False, c_result[1]
	return True, None



def checkProgramRequirements(program):
	defined_elements = {**program, **standard_elements_types_inputs_outputs}.keys()
	for name, description in program.items():
		elements = getElementsNumbers(description).keys()
		for e in elements:
			if not (e in defined_elements):
				return False, f'Function {name}: Element not declared: {e}'
	return True, None

def checkProgramInputsOutputs(program):
	defined_elements = {**program, **standard_elements_types_inputs_outputs}.keys()
	non_standard_elements_types_inputs_outputs = {}
	for name, description in program.items():
		inputs_outputs_for_type = getInputsOutputsNumbersForType(description)
		for t in description['tests']:
			for key in ['inputs', 'outputs']:
				have = len(t[key])
				should_have = inputs_outputs_for_type[key]
				if have != should_have:
					return False, f'Function {name}: Test {t}: {key} number does not match: have {have}, should have {should_have}'
		if inputs_outputs_for_type['inputs'] == 0:
			return False, f'Function {name}: 0 inputs'
		if inputs_outputs_for_type['outputs'] == 0:
			return False, f'Function {name}: 0 outputs'
		non_standard_elements_types_inputs_outputs[name] = inputs_outputs_for_type
	
	elements_types_inputs_outputs = {
		**standard_elements_types_inputs_outputs,
		**non_standard_elements_types_inputs_outputs
	}
	
	for f_name, description in program.items():
		elements_inputs_outputs = getInputsOutputsNumbersForInnerElements(description)
		for e_name, value in elements_inputs_outputs.items():
			e_type = getElementType(e_name)
			have = elements_inputs_outputs[e_name]
			have['outputs'] = bool(have['outputs'])
			should_have = elements_types_inputs_outputs[e_type]
			should_have['outputs'] = bool(should_have['outputs'])
			if have != should_have:
				return False, f'Function {f_name}: Element {e_name}: inputs/outputs do not match: have {have}, should have {should_have}'
	
	return True, None

def checkProgram(program, checks=[checkProgramRequirements, checkProgramInputsOutputs]):
	for c in checks:
		c_result = c(program)
		if not c_result[0]:
			return False, c_result[1]
	return True, None



def compile(file_path):
	result  = '#include <stdio.h>\n'
	result += '\n'
	result += '#define NOT(x) (!(x))\n'
	result += '#define OR(x, y) ((x) || (y))\n'
	result += '#define AND(x, y) ((x) && (y))\n'
	result += '#define OUTPUT(x) (x)\n'
	result += '\n'

	program = None
	with open('example.json', 'r') as f:
		program = json.load(f)

	check_program_result = checkProgram(program)
	if not check_program_result[0]:
		raise Exception(f'Program not correct: {check_program_result[1]}')

	outputs_numbers = {}
	definitions = ''
	for name, description in program.items():
		check_function_result = checkFunction(description)
		if not check_function_result[0]:
			raise Exception(f'Function "{name}" not correct: {check_function_result[1]}')
		definition, outputs_number = defineFunction(name, description)
		test_function_definition = defineTestFunction(name, description)
		definitions += '\n\n' + definition + '\n' + test_function_definition
		outputs_numbers[name] = outputs_number

	result += '#define FIRST(A, ...) A\n'
	result += '#define REST(A, ...) __VA_ARGS__\n'
	result += '\n'
	result += '#define NTH_1(...) FIRST(__VA_ARGS__)\n'
	result += '\n'

	for i in range(1, max(outputs_numbers.values())):
		result += f'#define NTH_{i + 1}(...) NTH_{i}(REST(__VA_ARGS__))\n'

	result += definitions
	result += '\n'
	result += '\n'
	result += f"""#define test__all {' && '.join([f'test_{name}' for name in program.keys()])}"""

	result += '\n'
	result += '\n'
	result += 'int main(void) {\n'
	result += '\tprintf("tests:\\n");\n'
	result += ''.join([f'\tprintf("\\t{name}: %s\\n", test_{name} ? "passed" : "failed");\n' for name in program.keys()])
	result += '\tprintf("%s\\n", test__all ? "All tests passed" : "Some tests failed");\n'
	result += '\treturn 0;\n'
	result += '}'

	return result