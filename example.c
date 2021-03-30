#include <stdio.h>
#include <stdlib.h>

#define INPUT(n) (INPUT[(n)-1])
#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define __xor__NOT_1 NOT(INPUT(1))
#define __xor__NOT_2 NOT(INPUT(2))
#define __xor__OR_2 OR(INPUT(1), INPUT(2))
#define __xor__OR_1 OR(__xor__NOT_1, __xor__NOT_2)
#define __xor__AND_1 AND(__xor__OR_1, __xor__OR_2)
#define __xor__OUTPUT_1 OUTPUT(__xor__AND_1)
#define xor() __xor__OUTPUT_1