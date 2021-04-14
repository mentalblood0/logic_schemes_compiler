inputs = [[x, y] for x in range(5) for y in range(5)]
f = lambda x, y: x + y
def int_to_bin_list(i):
	return list('{0:b}'.format(i))
convert_inputs_function = int_to_bin_list
convert_outputs_function = int_to_bin_list

def generateOneTest(inputs, f):
	f_result = f(*inputs)
	return {
		'inputs': [convert_inputs_function(e) for e in inputs],
		'outputs': [convert_outputs_function(f(i))]
	}

def generateTests(inputs, f, convert_inputs_function, convert_outputs_function):
	return list(map(lambda i: {
		'inputs': [convert_inputs_function(e) for e in i],
		'outputs': [convert_outputs_function(f(i))]
	}, inputs))

t = generateTests(inputs, f, convert_inputs_function, convert_outputs_function)
print(t[10])