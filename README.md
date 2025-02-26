# 📦 LSC — Logic Scheme to C compiler

[![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com)

## Why use LSC?

- You can use [this web-based editor](https://codeberg.org/mentalblood/logic_schemes_editor) to create and export schemes ✏️
- Super-easy to integrate with any other logic schemes editor 🔌
- Results in logic expressions, so C compiler can easily optimize them 🎯
- Supports nesting 📁

## Features

- Written in Python 🐍
- Takes JSON logic schemes representations 👀
- Checks JSON representation for errors 🧐
- Requires only wires "from, to" description ➡️
- Works with nested schemes (i.e defined scheme can be used in other schemes in file as element) 📁
- Scheme tests can be provided ✔️
- High full (JSON - C - executable) compilation speed 🚀

## Installation

```bash
pip install lsc-mentalblood
```

## Usage

```bash
python -m lsc [-h] -i INPUT [-t TARGET] -l [LINK ...] -o OUTPUT
```

arguments:

- `-i INPUT`, `--input INPUT` – path to file with target function
- `-t TARGET`, `--target TARGET` – name of function to compile
- `-l LINK`, `--link LINK` – paths to (input files) / (directories containing input files) with required functions descriptions
- `-o OUTPUT`, `--output OUTPUT` – path to output file

Also you can run

```bash
python -m lsc --help
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
        "inputs": [0, 0],
        "outputs": [0]
      },
      {
        "inputs": [1, 1],
        "outputs": [0]
      },
      {
        "inputs": [1, 0],
        "outputs": [1]
      },
      {
        "inputs": [0, 1],
        "outputs": [1]
      }
    ]
  }
}
```

command for compile:

```bash
python -m lsc --input lib\xor.json --target xor --link lib --output example.c
```

output code: [godbolt 📜](https://godbolt.org/z/c4TT5Trvv)

### Full bit adder

```json
{
  "sum": {
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
        "from": "AND_4[1]",
        "to": "OR_1[1]"
      },
      {
        "from": "AND_3_1[1]",
        "to": "OR_1[2]"
      },
      {
        "from": "OR_1[1]",
        "to": "OUTPUT_2[1]"
      }
    ],
    "tests": [
      {
        "inputs": [0, 0, 0],
        "outputs": [0, 0]
      },
      {
        "inputs": [0, 0, 1],
        "outputs": [0, 1]
      },
      {
        "inputs": [0, 1, 0],
        "outputs": [0, 1]
      },
      {
        "inputs": [1, 0, 0],
        "outputs": [0, 1]
      },
      {
        "inputs": [0, 1, 1],
        "outputs": [1, 0]
      },
      {
        "inputs": [1, 1, 0],
        "outputs": [1, 0]
      },
      {
        "inputs": [1, 0, 1],
        "outputs": [1, 0]
      },
      {
        "inputs": [1, 1, 1],
        "outputs": [1, 1]
      }
    ]
  }
}
```

command for compile:

```bash
python -m lsc --input lib\sum.json --target sum --link lib --output example.c
```

output code: [godbolt 📜](https://godbolt.org/z/b37a8ab47)

### Full 8bit adder (cascade)

```json
{
  "sum_8": {
    "wires": [
      {
        "from": "INPUT_16[1]",
        "to": "sum_1[1]"
      },
      {
        "from": "INPUT_8[1]",
        "to": "sum_1[2]"
      },
      {
        "from": "INPUT_7[1]",
        "to": "sum_2[2]"
      },
      {
        "from": "INPUT_15[1]",
        "to": "sum_2[1]"
      },
      {
        "from": "INPUT_17[1]",
        "to": "sum_1[3]"
      },
      {
        "from": "sum_1[1]",
        "to": "sum_2[3]"
      },
      {
        "from": "INPUT_6[1]",
        "to": "sum_3[2]"
      },
      {
        "from": "INPUT_14[1]",
        "to": "sum_3[1]"
      },
      {
        "from": "sum_2[1]",
        "to": "sum_3[3]"
      },
      {
        "from": "INPUT_5[1]",
        "to": "sum_4[2]"
      },
      {
        "from": "sum_3[1]",
        "to": "sum_4[3]"
      },
      {
        "from": "INPUT_1[1]",
        "to": "sum_8[2]"
      },
      {
        "from": "INPUT_9[1]",
        "to": "sum_8[1]"
      },
      {
        "from": "INPUT_2[1]",
        "to": "sum_7[2]"
      },
      {
        "from": "INPUT_10[1]",
        "to": "sum_7[1]"
      },
      {
        "from": "INPUT_11[1]",
        "to": "sum_6[1]"
      },
      {
        "from": "INPUT_3[1]",
        "to": "sum_6[2]"
      },
      {
        "from": "INPUT_12[1]",
        "to": "sum_5[1]"
      },
      {
        "from": "INPUT_4[1]",
        "to": "sum_5[2]"
      },
      {
        "from": "sum_4[1]",
        "to": "sum_5[3]"
      },
      {
        "from": "sum_5[1]",
        "to": "sum_6[3]"
      },
      {
        "from": "sum_6[1]",
        "to": "sum_7[3]"
      },
      {
        "from": "sum_7[1]",
        "to": "sum_8[3]"
      },
      {
        "from": "INPUT_13[1]",
        "to": "sum_4[1]"
      },
      {
        "from": "sum_8[1]",
        "to": "OUTPUT_1[1]"
      },
      {
        "from": "sum_8[2]",
        "to": "OUTPUT_2[1]"
      },
      {
        "from": "sum_1[2]",
        "to": "OUTPUT_9[1]"
      },
      {
        "from": "sum_2[2]",
        "to": "OUTPUT_8[1]"
      },
      {
        "from": "sum_3[2]",
        "to": "OUTPUT_7[1]"
      },
      {
        "from": "sum_4[2]",
        "to": "OUTPUT_6[1]"
      },
      {
        "from": "sum_5[2]",
        "to": "OUTPUT_5[1]"
      },
      {
        "from": "sum_6[2]",
        "to": "OUTPUT_4[1]"
      },
      {
        "from": "sum_7[2]",
        "to": "OUTPUT_3[1]"
      }
    ],
    "tests": [
      {
        "inputs": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 0, 0]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 0, 1]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 0, 1]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 1, 0]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 1, 0]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 0, 1, 0]
      },
      {
        "inputs": [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
        "outputs": [0, 0, 0, 0, 0, 0, 1, 0, 0]
      }
    ]
  }
}
```

command for compile:

```bash
python -m lsc --input lib\sum_8.json --target sum_8 --link lib --output example.c
```

output code: [godbolt 📜](https://godbolt.org/z/q471hr8Ee)
