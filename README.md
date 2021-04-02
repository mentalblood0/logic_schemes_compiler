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