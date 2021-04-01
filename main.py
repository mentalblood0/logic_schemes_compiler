import json

standard_elements = ['NOT', 'AND', 'OR', 'INPUT', 'OUTPUT']

def defineFunction(description):
	result = ''

	unique_elements = {}
	elements_inputs = {}
	for w in description['wires']:
		unique_elements[w['from']] = None
		unique_elements[w['to']] = None
		element = w['to'].split('[')[0]
		if not (element in elements_inputs):
			elements_inputs[element] = {}
		input_index = w['to'][:-1].split('[')[-1]
		try:
			elements_inputs[element][int(input_index)] = w['from']
		except ValueError:
			elements_inputs[element][0] = w['from']

	inputs_number = len(list(filter(lambda e: e.split('_')[0] == 'INPUT', unique_elements)))
	outputs_number = len(list(filter(lambda e: e.split('_')[0] == 'OUTPUT', unique_elements)))

	macros_prefix = '__' + description['name'] + '__'
	inputs_string = ', '.join([f'{macros_prefix}INPUT_{n}' for n in range(1, inputs_number+1)])
	
	for e in elements_inputs.keys():
		arguments_list = []
		for i in elements_inputs[e].values():
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
	
	result += '#define %s(%s) %s' % (
		description['name'],
		inputs_string,
		', '.join([f'{macros_prefix}OUTPUT_{n}({inputs_string})' for n in range(1, outputs_number+1)])
	)
	
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

	result += '''

int main(void) {
	printf("%d\\n", test_xor);
	printf("%d\\n", test_xorxor);
	return 0;
}'''

	return result