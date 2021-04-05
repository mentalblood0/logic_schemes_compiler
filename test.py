import main

file_path = 'example.json'
compiled = main.compile(file_path)

# print(compiled)
compiled_path = 'example.c'
with open(compiled_path, 'w') as f:
	f.write(compiled)