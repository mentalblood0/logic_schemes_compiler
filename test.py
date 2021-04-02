import main

file_path = 'example.json'
try:
	compiled = main.compile(file_path)
except Exception as e:
	print(e)
	exit(1)
# print(compiled)
compiled_path = 'example.c'
with open(compiled_path, 'w') as f:
	f.write(compiled)