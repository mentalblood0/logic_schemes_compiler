#include <stdio.h>
#include <stdlib.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define __xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2) NOT(__xor__INPUT_1(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2) NOT(__xor__INPUT_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2) OR(__xor__INPUT_1(__xor__INPUT_1, __xor__INPUT_2), __xor__INPUT_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__OR_1(__xor__INPUT_1, __xor__INPUT_2) OR(__xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2), __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__AND_1(__xor__INPUT_1, __xor__INPUT_2) AND(__xor__OR_1(__xor__INPUT_1, __xor__INPUT_2), __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2) OUTPUT(__xor__AND_1(__xor__INPUT_1, __xor__INPUT_2))
#define xor(__xor__INPUT_1, __xor__INPUT_2) __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2)

#define __xorxor__xor_1(__xorxor__INPUT_1, __xorxor__INPUT_2) xor(__xorxor__INPUT_1(__xorxor__INPUT_1, __xorxor__INPUT_2), __xorxor__INPUT_2(__xorxor__INPUT_1, __xorxor__INPUT_2))
#define __xorxor__xor_2(__xorxor__INPUT_1, __xorxor__INPUT_2) xor(__xorxor__INPUT_1(__xorxor__INPUT_1, __xorxor__INPUT_2), __xorxor__INPUT_2(__xorxor__INPUT_1, __xorxor__INPUT_2))
#define __xorxor__xor_3(__xorxor__INPUT_1, __xorxor__INPUT_2) xor(__xorxor__xor_1(__xorxor__INPUT_1, __xorxor__INPUT_2), __xorxor__xor_2(__xorxor__INPUT_1, __xorxor__INPUT_2))
#define __xorxor__OUTPUT_1(__xorxor__INPUT_1, __xorxor__INPUT_2) OUTPUT(__xorxor__xor_3(__xorxor__INPUT_1, __xorxor__INPUT_2))
#define xorxor(__xorxor__INPUT_1, __xorxor__INPUT_2) __xorxor__OUTPUT_1(__xorxor__INPUT_1, __xorxor__INPUT_2)