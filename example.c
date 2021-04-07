#include <stdio.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_1(...) FIRST(__VA_ARGS__)



#define __xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2) NOT(NTH_1(__xor__INPUT_1))
#define __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2) NOT(NTH_1(__xor__INPUT_2))
#define __xor__OR_1(__xor__INPUT_1, __xor__INPUT_2) OR(NTH_1(__xor__INPUT_1), NTH_1(__xor__INPUT_2))
#define __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2) OR(NTH_1(__xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2)), NTH_1(__xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2)))
#define __xor__AND_1(__xor__INPUT_1, __xor__INPUT_2) AND(NTH_1(__xor__OR_1(__xor__INPUT_1, __xor__INPUT_2)), NTH_1(__xor__OR_2(__xor__INPUT_1, __xor__INPUT_2)))
#define __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2) OUTPUT(NTH_1(__xor__AND_1(__xor__INPUT_1, __xor__INPUT_2)))
#define xor(__xor__INPUT_1, __xor__INPUT_2) __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2)

#define __MAIN__xor_1(__MAIN__INPUT_1, __MAIN__INPUT_2) xor(NTH_1(__MAIN__INPUT_2), NTH_1(__MAIN__INPUT_1))
#define __MAIN__xor_2(__MAIN__INPUT_1, __MAIN__INPUT_2) xor(NTH_1(__MAIN__xor_1(__MAIN__INPUT_1, __MAIN__INPUT_2)), NTH_1(__MAIN__xor_1(__MAIN__INPUT_1, __MAIN__INPUT_2)))
#define __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2) OUTPUT(NTH_1(__MAIN__xor_2(__MAIN__INPUT_1, __MAIN__INPUT_2)))
#define MAIN(__MAIN__INPUT_1, __MAIN__INPUT_2) __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2)



int main(void) {
}