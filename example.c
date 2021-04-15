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

#define NTH_2(...) NTH_1(REST(__VA_ARGS__))


#define __OR_3__OR_2(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OR(NTH_1(__OR_3__INPUT_1), NTH_1(__OR_3__INPUT_2))
#define __OR_3__OR_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OR(NTH_1(__OR_3__OR_2(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)), NTH_1(__OR_3__INPUT_3))
#define __OR_3__OUTPUT_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OUTPUT(NTH_1(__OR_3__OR_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)))
#define OR_3(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) __OR_3__OUTPUT_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)

#define __AND_3__AND_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) AND(NTH_1(__AND_3__INPUT_1), NTH_1(__AND_3__INPUT_2))
#define __AND_3__AND_2(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) AND(NTH_1(__AND_3__AND_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)), NTH_1(__AND_3__INPUT_3))
#define __AND_3__OUTPUT_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) OUTPUT(NTH_1(__AND_3__AND_2(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)))
#define AND_3(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) __AND_3__OUTPUT_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)

#define __SUM__AND_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) AND(NTH_1(__SUM__INPUT_1), NTH_1(__SUM__INPUT_2))
#define __SUM__AND_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) AND(NTH_1(__SUM__INPUT_1), NTH_1(__SUM__INPUT_3))
#define __SUM__OR_3_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) OR_3(NTH_1(__SUM__INPUT_1), NTH_1(__SUM__INPUT_2), NTH_1(__SUM__INPUT_3))
#define __SUM__AND_3_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) AND_3(NTH_1(__SUM__INPUT_1), NTH_1(__SUM__INPUT_2), NTH_1(__SUM__INPUT_3))
#define __SUM__AND_3(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) AND(NTH_1(__SUM__INPUT_2), NTH_1(__SUM__INPUT_3))
#define __SUM__OR_3_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) OR_3(NTH_1(__SUM__AND_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)), NTH_1(__SUM__AND_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)), NTH_1(__SUM__AND_3(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define __SUM__OUTPUT_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) OUTPUT(NTH_1(__SUM__OR_3_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define __SUM__NOT_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) NOT(NTH_1(__SUM__OR_3_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define __SUM__AND_4(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) AND(NTH_1(__SUM__NOT_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)), NTH_1(__SUM__OR_3_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define __SUM__OR_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) OR(NTH_1(__SUM__AND_3_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)), NTH_1(__SUM__AND_4(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define __SUM__OUTPUT_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) OUTPUT(NTH_1(__SUM__OR_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)))
#define SUM(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3) __SUM__OUTPUT_1(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3), __SUM__OUTPUT_2(__SUM__INPUT_1, __SUM__INPUT_2, __SUM__INPUT_3)

#define test__all test_SUM

int main(void) {
	printf("tests:\n");
	int i;	printf("\tSUM:\n");
	int tests_SUM__inputs[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
	int tests_SUM__outputs[8][3] = {{0, 0}, {0, 1}, {0, 1}, {1, 0}, {0, 1}, {1, 0}, {1, 0}, {1, 1}};
	for (i = 0; i < 8; i++) {
		int output[2] = {SUM(tests_SUM__inputs[i][0], tests_SUM__inputs[i][1], tests_SUM__inputs[i][2])};
		printf("\t\t[%d, %d, %d] => [%d, %d]: %s\n", tests_SUM__inputs[i][0], tests_SUM__inputs[i][1], tests_SUM__inputs[i][2], output[0], output[1], ((tests_SUM__outputs[i][0] == output[0]) && (tests_SUM__outputs[i][1] == output[1])) ? "passed" : "failed");
	}
	return 0;
}