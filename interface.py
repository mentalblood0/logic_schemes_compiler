import core
import argparse

parser = argparse.ArgumentParser(description='Compile logic schemes JSON representations to C file')
parser.add_argument('--input', type=str, nargs='+',
                    help='Paths to (input files) / (directories containing input files)', default=None)
parser.add_argument('--output', type=str,
                    help='Path to output file', default=None)
args = parser.parse_args()

print(args)
exit()

file_path = 'example.json'
compiled = main.compile(file_path)

# print(compiled)
compiled_path = 'example.c'
with open(compiled_path, 'w') as f:
	f.write(compiled)