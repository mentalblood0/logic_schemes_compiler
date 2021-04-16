#include <stdio.h>

#define NOT(x) !x
#define OR(x, y) (x || y)
#define AND(x, y) (x && y)
#define OUTPUT(...) __VA_ARGS__

#define xstr(...) str(__VA_ARGS__)
#define str(...) #__VA_ARGS__
#define equal(x, y) xstr(x) == xstr(y)

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_1(...) FIRST(__VA_ARGS__)



#define __xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2) NOT(NTH_1(__xor__INPUT_1))
#define __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2) NOT(NTH_1(__xor__INPUT_2))
#define __xor__OR_1(__xor__INPUT_1, __xor__INPUT_2) OR(NTH_1(__xor__INPUT_2), NTH_1(__xor__INPUT_1))
#define __xor__AND_1(__xor__INPUT_1, __xor__INPUT_2) AND(NTH_1(__xor__OR_1(__xor__INPUT_1, __xor__INPUT_2)), NTH_1(__xor__OR_2(__xor__INPUT_1, __xor__INPUT_2)))
#define __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2) OUTPUT(NTH_1(__xor__AND_1(__xor__INPUT_1, __xor__INPUT_2)))
#define __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2) OR(NTH_1(__xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2)), NTH_1(__xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2)))
#define xor(__xor__INPUT_1, __xor__INPUT_2) __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2)

#define test__all test_xor

int main(void) {
	printf("tests:\n");
	int i;	printf("\txor:\n");
	int tests_xor__inputs[4][2] = {{0, 0}, {1, 1}, {1, 0}, {0, 1}};
	int tests_xor__outputs[4][2] = {{0}, {0}, {1}, {1}};
	for (i = 0; i < 4; i++) {
		int output[1] = {xor(tests_xor__inputs[i][0], tests_xor__inputs[i][1])};
		printf("\t\t[%d, %d] => [%d]: %s\n", tests_xor__inputs[i][0], tests_xor__inputs[i][1], output[0], ((tests_xor__outputs[i][0] == output[0])) ? "passed" : "failed");
	}
	return 0;
}