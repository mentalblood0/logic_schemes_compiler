#include <stdio.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_1(...) FIRST(__VA_ARGS__)



#define __test__NOT_0(__test__INPUT_1, __test__INPUT_2) NOT(__test__INPUT_0[0])
#define __test__NOT_1(__test__INPUT_1, __test__INPUT_2) NOT(__test__INPUT_1[0])
#define __test__OR_0(__test__INPUT_1, __test__INPUT_2) OR(__test__INPUT_1[0], __test__INPUT_0[0])
#define __test__OR_1(__test__INPUT_1, __test__INPUT_2) OR(NTH_0(__test__NOT_0(__test__INPUT_1, __test__INPUT_2)), NTH_0(__test__NOT_1(__test__INPUT_1, __test__INPUT_2)))
#define __test__AND_0(__test__INPUT_1, __test__INPUT_2) AND(NTH_0(__test__OR_0(__test__INPUT_1, __test__INPUT_2)), NTH_0(__test__OR_1(__test__INPUT_1, __test__INPUT_2)))
#define __test__OUTPUT_0(__test__INPUT_1, __test__INPUT_2) OUTPUT(NTH_0(__test__AND_0(__test__INPUT_1, __test__INPUT_2)))
#define test(__test__INPUT_1, __test__INPUT_2) __test__OUTPUT_1(__test__INPUT_1, __test__INPUT_2)



int main(void) {
}