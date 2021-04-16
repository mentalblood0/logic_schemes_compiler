import json

standard_elements = {
	'NOT': 		{'inputs': 1, 'outputs': 1},
	'AND': 		{'inputs': 2, 'outputs': 1},
	'OR': 		{'inputs': 2, 'outputs': 1},
	'INPUT': 	{'inputs': 0, 'outputs': 1},
	'OUTPUT': 	{'inputs': 1, 'outputs': 0}
}

def getElementType(element):
	return '_'.join(element.split('_')[:-1])

def getElementName(element_input_or_output):
	return element_input_or_output.split('[')[0]

def getInputOutputIndex(element_input_or_output):
	return element_input_or_output[:-1].split('[')[1]

def getElementsTypes(description):
	result = {}
	for e in sum([[w['from'], w['to']] for w in description['wires']], []):
		element_type = getElementType(e)
		result[element_type] = None
	return result.keys()

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
		element = getElementName(w['to'])
		if not (element in result):
			result[element] = {}
		input_index = getInputOutputIndex(w['to'])
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
			i_without_index = getElementName(i)
			number_of_output_to_take = getInputOutputIndex(i)
			if getElementType(i) != 'INPUT':
				argument = f"NTH_{number_of_output_to_take}({macros_prefix}{i_without_index}({inputs_string}))"
			else:
				argument = f"NTH_{number_of_output_to_take}({macros_prefix}{i_without_index})"
			arguments_list.append(argument)
		arguments = ', '.join(arguments_list)
		result += f"#define {macros_prefix}{e}({inputs_string}) {getElementType(e)}({arguments})\n"
	
	function_outputs_string = ', '.join([
		f'{macros_prefix}OUTPUT_{n}({inputs_string})'
		for n in range(1, outputs_number + 1)
	])
	result += f"#define {name}({inputs_string}) {function_outputs_string}"
	
	return result, outputs_number

def defineTestFunction(name, description):
	equalities_list = []
	inputs_number = len(description['tests'][0]['inputs'])
	outputs_number = len(description['tests'][0]['outputs'])
	tests_number = len(description['tests'])
	for t in description['tests']:
		inputs_string = ', '.join(map(str, t['inputs']))
		equalities_list.append(f"{name}({inputs_string}) == OUTPUT({', '.join(map(str, t['outputs']))})")
	result = '\n'.join([
		f"int test_{name}__{i + 1}() {{return {equalities_list[i]};}}"
		for i in range(len(equalities_list))
	])
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
		from_element = getElementName(w['from'])
		to_element = getElementName(w['to'])
		if not from_element in from_to:
			from_to[from_element] = []
		from_to[from_element].append(to_element)
	
	inputs = [e for e in from_to if getElementType(e) == 'INPUT']
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
	defined_elements = {**program, **standard_elements}.keys()
	for name, description in program.items():
		elements = getElementsTypes(description)
		for e in elements:
			if not (e in defined_elements):
				return False, f'Function {name}: Element not declared: {e}'
	return True, None

def checkProgramInputsOutputs(program):
	defined_elements = {**program, **standard_elements}.keys()
	non_standard_elements = {}
	for name, description in program.items():
		inputs_outputs_for_type = getInputsOutputsNumbersForType(description)
		non_standard_elements[name] = inputs_outputs_for_type
		if 'tests' in description:
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
	
	elements_types_inputs_outputs = {
		**standard_elements,
		**non_standard_elements
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



def compile(program):
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
		definitions += '\n\n' + definition
		# if 'tests' in description:
		# 	test_function_definition = defineTestFunction(name, description)
		# 	definitions += '\n' + test_function_definition
		outputs_numbers[name] = outputs_number

	result  = '#include <stdio.h>\n'
	result += '\n'
	result += '#define NOT(x) !x\n'
	result += '#define OR(x, y) (x || y)\n'
	result += '#define AND(x, y) (x && y)\n'
	result += '#define OUTPUT(...) __VA_ARGS__\n'
	result += '\n'
	result += '#define xstr(...) str(__VA_ARGS__)\n'
	result += '#define str(...) #__VA_ARGS__\n'
	result += '#define equal(x, y) xstr(x) == xstr(y)\n'
	result += '\n'
	result += '#define FIRST(A, ...) A\n'
	result += '#define REST(A, ...) __VA_ARGS__\n'
	result += '\n'
	result += '#define NTH_1(...) FIRST(__VA_ARGS__)\n'
	result += '\n'

	for i in range(1, max(outputs_numbers.values())):
		result += f'#define NTH_{i + 1}(...) NTH_{i}(REST(__VA_ARGS__))\n'

	functions_names_with_tests = [name for name in program.keys() if 'tests' in program[name]]

	result += definitions
	result += '\n'
	result += '\n'
	if len(functions_names_with_tests) > 0:
		result += f"""#define test__all {' && '.join([f'test_{name}' for name in functions_names_with_tests])}"""

	result += '\n'
	result += '\n'
	result += 'int main(void) {\n'
	if len(functions_names_with_tests) > 0:
		result += '\tprintf("tests:\\n");\n'
		result += '\tint i;'
		for name in functions_names_with_tests:
			tests_number = len(program[name]['tests'])
			inputs_number = len(program[name]['tests'][0]['inputs'])
			outputs_number = len(program[name]['tests'][0]['outputs'])
			result += f'\tprintf("\\t{name}:\\n");\n'
			for s in ['inputs', 'outputs']:
				list_init_values_list = map(lambda i: f"{{{i}}}", [", ".join(map(str, t[s])) for t in program[name]['tests']])
				result += f'\tint tests_{name}__{s}[{tests_number}][{inputs_number}] = {{{", ".join(list_init_values_list)}}};\n'
			result += f'\tfor (i = 0; i < {tests_number}; i++) {{\n'
			inputs_values_list = [f'tests_{name}__inputs[i][{j}]' for j in range(inputs_number)]
			outputs_values_list = [f'tests_{name}__outputs[i][{j}]' for j in range(outputs_number)]
			result += f'\t\tint output[{outputs_number}] = {{{name}({", ".join(inputs_values_list)})}};\n'
			printf_template_for_inputs = f'[{", ".join(["%d" for i in range(inputs_number)])}]'
			printf_template_for_outputs = f'[{", ".join(["%d" for i in range(outputs_number)])}]'
			printf_values_for_inputs = ', '.join(inputs_values_list)
			# printf_values_for_outputs = ', '.join([f'output[{i}]' for i in range(outputs_number)])
			printf_values_for_outputs = ', '.join(outputs_values_list)
			result += f'\t\tprintf("\\t\\t{printf_template_for_inputs} => {printf_template_for_outputs}: %s\\n", {printf_values_for_inputs}, {printf_values_for_outputs}, ({" && ".join([f"({outputs_values_list[i]} == output[{i}])" for i in range(len(outputs_values_list))])}) ? "passed" : "failed");\n'
			result += '\t}\n'
		result += '\treturn 0;\n'
	result += '}'

	return result