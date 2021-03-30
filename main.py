import json

def compile(file_path):
	result = '''#include <stdio.h>
#include <stdlib.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

'''
	program = None
	with open('example.json', 'r') as f:
		program = json.load(f)
	result += '\n\n'.join([defineFunction(description) for description in program])
	return result

def defineFunction(description):
	result = ''

	unique_elements = {}
	elements_inputs = {}
	for w in description['wires']:
		unique_elements[w['from']] = None
		unique_elements[w['to']] = None
		element = w['to']
		if not (element in elements_inputs):
			elements_inputs[element] = []
		elements_inputs[element].append(w['from'])

	inputs_number = len(list(filter(lambda e: e.split('_')[0] == 'INPUT', unique_elements)))
	outputs_number = len(list(filter(lambda e: e.split('_')[0] == 'OUTPUT', unique_elements)))

	macros_prefix = '__' + description['name'] + '__'
	inputs_string = ', '.join([f'{macros_prefix}INPUT_{n}' for n in range(1, inputs_number+1)])
	
	for e in elements_inputs:
		result += "#define %s%s(%s) %s(%s)\n" % (
			macros_prefix,
			e,
			inputs_string,
			e.split('_')[0],
			', '.join([(f'{macros_prefix}{i}({inputs_string})') if (i.split('_')[-2] != f'{macros_prefix}INPUT') else i for i in elements_inputs[e]])
		)
	
	result += '#define %s(%s) %s(%s)' % (
		description['name'],
		inputs_string,
		', '.join([f'{macros_prefix}OUTPUT_{n}' for n in range(1, outputs_number+1)]),
		inputs_string
	)
	
	return result