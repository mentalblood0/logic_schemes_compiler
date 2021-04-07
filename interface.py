import core
import argparse
import os
import json

parser = argparse.ArgumentParser(description='Compile logic schemes JSON representations to C file')
parser.add_argument('-i', '--input', type=str,
					required=True,
                    help='Path to file with target function', default=None)
parser.add_argument('-t', '--target', type=str,
					help='Name of function to compile', default='MAIN')
parser.add_argument('-l', '--link', type=str, nargs='*',
					required=True,
					help='Paths to (input files) / (directories containing input files) with required functions descriptions', default=None)
parser.add_argument('-o', '--output', type=str,
					required=True,
					help='Path to output file', default=None)
args = parser.parse_args()

input_path = args.input
target_function_name = args.target
linked_paths = args.link
output_path = args.output

def joinPrograms(subpaths, root='.'):
	result = {}
	for sp in subpaths:
		p = os.path.join(root, sp)
		if not os.path.exists(p):
			print(f'No file/dir on path: {p}, skiping')
		elif os.path.isdir(p):
			dir_content = list(filter(
				lambda p: p.endswith('.json') or os.path.isdir(p),
				os.listdir(p)
			))
			if len(dir_content) > 0:
				result = {**result, **joinPrograms(dir_content, root=p)}
		else:
			with open(p) as f:
				result = {**result, **json.load(f)}
	return result

available_functions_descriptions = joinPrograms([input_path] + linked_paths)
del available_functions_descriptions[target_function_name]
with open(input_path) as f:
	target_function_description = json.load(f)[target_function_name]

def getNonstandardRequirements(
	target_function_name,
	target_function_description,
	available_functions_descriptions
):
	direct_requirements = core.getElementsTypes(target_function_description)
	direct_nonstandard_requirements = list(filter(
		lambda e: not (e in core.standard_elements),
		direct_requirements
	))
	indirect_nonstandard_requirements = []
	for d_r in direct_nonstandard_requirements:
		if not (d_r in available_functions_descriptions):
			raise Exception(f'Compile error: {target_function_name} requires {d_r}, but it is not presented')
		d_r_description = available_functions_descriptions[d_r]
		d_r_nonstandard_requirements = getNonstandardRequirements(
			d_r,
			d_r_description,
			available_functions_descriptions
		)
		indirect_nonstandard_requirements += d_r_nonstandard_requirements
	return list(set(direct_nonstandard_requirements + indirect_nonstandard_requirements))

requirements = getNonstandardRequirements(
	target_function_name,
	target_function_description,
	available_functions_descriptions
)
program = {
	**{
		r_name: available_functions_descriptions[r_name]
		for r_name in requirements
	}, **{
		target_function_name: target_function_description
	}
}

compiled_program = core.compile(program)


with open(output_path, 'w') as f:
	f.write(compiled_program)