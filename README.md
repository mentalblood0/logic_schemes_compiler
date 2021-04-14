# 📦 LSC —  Logic Scheme to C compiler

## Features

- Written in Python 🐍
- Takes JSON logic schemes representations 👀
- Checks JSON representation for errors 🧐
- Requires only wires "from, to" description ➡️
- Works with nested schemes (i.e defined scheme can be used in other schemes in file as element) 📁
- Scheme tests can be provided ✔️

- Compiles JSON representation to C file using **only macros** 🤓

## Usage

```bash
usage: interface.py [-h] -i INPUT [-t TARGET] -l [LINK ...] -o OUTPUT

Compile logic schemes JSON representations to C file

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        Path to file with target function
  -t TARGET, --target TARGET
                        Name of function to compile
  -l [LINK ...], --link [LINK ...]
                        Paths to (input files) / (directories containing input files) with required functions descriptions
  -o OUTPUT, --output OUTPUT
                        Path to output file
```



## Examples

### XOR

```json
{
	"xor": {
		"wires": [
			{
				"from": "INPUT_2[1]",
				"to": "NOT_2[1]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "NOT_1[1]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "OR_1[1]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "OR_1[2]"
			},
			{
				"from": "NOT_1[1]",
				"to": "OR_2[1]"
			},
			{
				"from": "NOT_2[1]",
				"to": "OR_2[2]"
			},
			{
				"from": "OR_1[1]",
				"to": "AND_1[2]"
			},
			{
				"from": "AND_1[1]",
				"to": "OUTPUT_1[1]"
			},
			{
				"from": "OR_2[1]",
				"to": "AND_1[1]"
			}
		],
		"tests": [
			{
				"inputs": [
					0,
					0
				],
				"outputs": [
					0
				]
			},
			{
				"inputs": [
					1,
					1
				],
				"outputs": [
					0
				]
			},
			{
				"inputs": [
					1,
					0
				],
				"outputs": [
					1
				]
			},
			{
				"inputs": [
					0,
					1
				],
				"outputs": [
					1
				]
			}
		]
	}
}
```

command for compile:

`python interface.py --input lib\xor.json --target xor --link lib --output example.c`

output code: [godbolt 📜](https://godbolt.org/z/8MvfbvMWx) 

### Full bit adder

```json
{
	"SUM": {
		"wires": [
			{
				"from": "INPUT_1[1]",
				"to": "AND_1[1]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "AND_2[1]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "OR_3_1[1]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "AND_3_1[1]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "AND_1[2]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "AND_3[1]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "OR_3_1[2]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "AND_3_1[2]"
			},
			{
				"from": "INPUT_3[1]",
				"to": "AND_2[2]"
			},
			{
				"from": "INPUT_3[1]",
				"to": "AND_3[2]"
			},
			{
				"from": "INPUT_3[1]",
				"to": "OR_3_1[3]"
			},
			{
				"from": "INPUT_3[1]",
				"to": "AND_3_1[3]"
			},
			{
				"from": "AND_1[1]",
				"to": "OR_3_2[1]"
			},
			{
				"from": "AND_2[1]",
				"to": "OR_3_2[2]"
			},
			{
				"from": "AND_3[1]",
				"to": "OR_3_2[3]"
			},
			{
				"from": "OR_3_2[1]",
				"to": "OUTPUT_1[1]"
			},
			{
				"from": "OR_3_2[1]",
				"to": "NOT_1[1]"
			},
			{
				"from": "NOT_1[1]",
				"to": "AND_4[1]"
			},
			{
				"from": "OR_3_1[1]",
				"to": "AND_4[2]"
			},
			{
				"from": "AND_3_1[1]",
				"to": "OR_1[2]"
			},
			{
				"from": "AND_4[1]",
				"to": "OR_1[1]"
			},
			{
				"from": "OR_1[1]",
				"to": "OUTPUT_2[1]"
			}
		],
		"tests": [
			{
				"inputs": [
					0,
					0,
					0
				],
				"outputs": [
					0,
					0
				]
			},
			{
				"inputs": [
					0,
					0,
					1
				],
				"outputs": [
					0,
					1
				]
			},
			{
				"inputs": [
					0,
					1,
					0
				],
				"outputs": [
					0,
					1
				]
			},
			{
				"inputs": [
					0,
					1,
					1
				],
				"outputs": [
					1,
					0
				]
			},
			{
				"inputs": [
					1,
					0,
					0
				],
				"outputs": [
					0,
					1
				]
			},
			{
				"inputs": [
					1,
					0,
					1
				],
				"outputs": [
					1,
					0
				]
			},
			{
				"inputs": [
					1,
					1,
					0
				],
				"outputs": [
					1,
					0
				]
			},
			{
				"inputs": [
					1,
					1,
					1
				],
				"outputs": [
					1,
					1
				]
			}
		]
	}
}
```

command for compile:

`python interface.py --input lib\SUM.json --target SUM --link lib --output example.c`

output code: [godbolt 📜](https://godbolt.org/z/eesEbvdjb) 

### Full 8bit adder (cascade)

```json
{
	"C_SUM_8": {
		"wires": [
			{
				"from": "INPUT_8[1]",
				"to": "SUM_4[1]"
			},
			{
				"from": "INPUT_16[1]",
				"to": "SUM_4[2]"
			},
			{
				"from": "INPUT_17[1]",
				"to": "SUM_4[3]"
			},
			{
				"from": "INPUT_7[1]",
				"to": "SUM_3[1]"
			},
			{
				"from": "INPUT_15[1]",
				"to": "SUM_3[2]"
			},
			{
				"from": "SUM_4[1]",
				"to": "SUM_3[3]"
			},
			{
				"from": "INPUT_6[1]",
				"to": "SUM_2[1]"
			},
			{
				"from": "INPUT_14[1]",
				"to": "SUM_2[2]"
			},
			{
				"from": "SUM_3[1]",
				"to": "SUM_2[3]"
			},
			{
				"from": "INPUT_5[1]",
				"to": "SUM_1[1]"
			},
			{
				"from": "INPUT_13[1]",
				"to": "SUM_1[2]"
			},
			{
				"from": "SUM_2[1]",
				"to": "SUM_1[3]"
			},
			{
				"from": "SUM_1[1]",
				"to": "SUM_5[3]"
			},
			{
				"from": "INPUT_12[1]",
				"to": "SUM_5[2]"
			},
			{
				"from": "INPUT_4[1]",
				"to": "SUM_5[1]"
			},
			{
				"from": "INPUT_3[1]",
				"to": "SUM_6[1]"
			},
			{
				"from": "INPUT_11[1]",
				"to": "SUM_6[2]"
			},
			{
				"from": "INPUT_2[1]",
				"to": "SUM_7[1]"
			},
			{
				"from": "INPUT_10[1]",
				"to": "SUM_7[2]"
			},
			{
				"from": "INPUT_9[1]",
				"to": "SUM_8[2]"
			},
			{
				"from": "INPUT_1[1]",
				"to": "SUM_8[1]"
			},
			{
				"from": "SUM_5[1]",
				"to": "SUM_6[3]"
			},
			{
				"from": "SUM_6[1]",
				"to": "SUM_7[3]"
			},
			{
				"from": "SUM_7[1]",
				"to": "SUM_8[3]"
			},
			{
				"from": "SUM_8[1]",
				"to": "OUTPUT_1[1]"
			},
			{
				"from": "SUM_8[2]",
				"to": "OUTPUT_2[1]"
			},
			{
				"from": "SUM_1[2]",
				"to": "OUTPUT_6[1]"
			},
			{
				"from": "SUM_2[2]",
				"to": "OUTPUT_7[1]"
			},
			{
				"from": "SUM_3[2]",
				"to": "OUTPUT_8[1]"
			},
			{
				"from": "SUM_4[2]",
				"to": "OUTPUT_9[1]"
			},
			{
				"from": "SUM_7[2]",
				"to": "OUTPUT_3[1]"
			},
			{
				"from": "SUM_6[2]",
				"to": "OUTPUT_4[1]"
			},
			{
				"from": "SUM_5[2]",
				"to": "OUTPUT_5[1]"
			}
		],
		"tests": [
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0
				]
			},
			{
				"inputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0
				],
				"outputs": [
					0,
					0,
					0,
					0,
					0,
					0,
					1,
					0,
					0
				]
			}
		]
	}
}
```

command for compile:

`python interface.py --input lib\C_SUM_8.json --target C_SUM_8 --link lib --output example.c` 

output code: [godbolt 📜](https://godbolt.org/z/Esox1zGWc) 

## Benefits

- Super-easy to integrate with any logic schemes editor 🔌
- Results in macros, so C compiler can easily optimize them 🎯
- Supports nesting 📁

## So

You can

- Rapidly develop complex schemes 💪
- While keeping calculation speed high 🚀
- Without worrying about optimization 😇