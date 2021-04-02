# LSC —  Logic Scheme to C compiler

## Features

### Ordinary part

- Written in Python
- Takes JSON logic schemes representations
- Checks JSON representation for errors
- Requires only wires "from, to" description
- Works with nested schemes (i.e defined scheme can be used in other schemes in file as element)
- Scheme tests can be provided

### Unique part

- Compiles JSON representation to C file using **only macros**
- Tests compiled using only macros, too

## Examples

### XOR

```json
{
	"xor": {
		"wires": [
			{"from": "INPUT_1", "to": "NOT_1"},
			{"from": "INPUT_2", "to": "NOT_2"},
			{"from": "INPUT_1", "to": "OR_2[1]"},
			{"from": "INPUT_2", "to": "OR_2[2]"},
			{"from": "NOT_1", "to": "OR_1[1]"},
			{"from": "NOT_2", "to": "OR_1[2]"},
			{"from": "OR_1", "to": "AND_1[1]"},
			{"from": "OR_2", "to": "AND_1[2]"},
			{"from": "AND_1", "to": "OUTPUT_1"}
		],
		"tests": [
			{"inputs": [0, 0], "outputs": [0]},
			{"inputs": [1, 0], "outputs": [1]},
			{"inputs": [0, 1], "outputs": [1]},
			{"inputs": [1, 1], "outputs": [0]}
		]
	}
}
```

output code: [godbolt](https://godbolt.org/z/do3hc675e)

### XOR of XORs

```json
{
	"xorxor": {
		"wires": [
			{"from": "INPUT_1", "to": "xor_1[1]"},
			{"from": "INPUT_2", "to": "xor_1[2]"},
			{"from": "INPUT_1", "to": "xor_2[1]"},
			{"from": "INPUT_2", "to": "xor_2[2]"},
			{"from": "xor_1[1]", "to": "xor_3[1]"},
			{"from": "xor_2[1]", "to": "xor_3[2]"},
			{"from": "xor_3[1]", "to": "OUTPUT_1"}	
		],
		"tests": [
			{"inputs": [0, 0], "outputs": [0]},
			{"inputs": [1, 0], "outputs": [0]},
			{"inputs": [0, 1], "outputs": [0]},
			{"inputs": [1, 1], "outputs": [0]}
		]
	},
	"xor": {
		"wires": [
			{"from": "INPUT_1", "to": "NOT_1"},
			{"from": "INPUT_2", "to": "NOT_2"},
			{"from": "INPUT_1", "to": "OR_2[1]"},
			{"from": "INPUT_2", "to": "OR_2[2]"},
			{"from": "NOT_1", "to": "OR_1[1]"},
			{"from": "NOT_2", "to": "OR_1[2]"},
			{"from": "OR_1", "to": "AND_1[1]"},
			{"from": "OR_2", "to": "AND_1[2]"},
			{"from": "AND_1", "to": "OUTPUT_1"}
		],
		"tests": [
			{"inputs": [0, 0], "outputs": [0]},
			{"inputs": [1, 0], "outputs": [1]},
			{"inputs": [0, 1], "outputs": [1]},
			{"inputs": [1, 1], "outputs": [0]}
		]
	}
}
```

output code: [godbolt](https://godbolt.org/z/WT9Pq9qP5)

## Benefits

- Super-easy to integrate with any logic schemes editor
- Results in macros, so C compiler can easily optimize them
- Supports nesting

## So

You can

- Rapidly develop complex schemes
- While keeping calculation speed high
- Without worrying about optimization 