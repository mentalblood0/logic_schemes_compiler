#include <stdio.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_0(...) FIRST(__VA_ARGS__)

#define NTH_1(...) NTH_0(REST(__VA_ARGS__))


#define __MAIN__xor_1(__MAIN__INPUT_1, __MAIN__INPUT_2) xor(__MAIN__INPUT_1, __MAIN__INPUT_2)
#define __MAIN__xor_2(__MAIN__INPUT_1, __MAIN__INPUT_2) xor(__MAIN__INPUT_1, __MAIN__INPUT_2)
#define __MAIN__xor_3(__MAIN__INPUT_1, __MAIN__INPUT_2) xor(NTH_1(__MAIN__xor_1(__MAIN__INPUT_1, __MAIN__INPUT_2)), NTH_1(__MAIN__xor_2(__MAIN__INPUT_1, __MAIN__INPUT_2)))
#define __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2) OUTPUT(NTH_1(__MAIN__xor_3(__MAIN__INPUT_1, __MAIN__INPUT_2)))
#define MAIN(__MAIN__INPUT_1, __MAIN__INPUT_2) __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2)
#define test_MAIN ((NTH_0(MAIN(0, 0)) == 0) && (NTH_0(MAIN(1, 0)) == 0) && (NTH_0(MAIN(0, 1)) == 0) && (NTH_0(MAIN(1, 1)) == 0))

#define __xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2) NOT(__xor__INPUT_1)
#define __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2) NOT(__xor__INPUT_2)
#define __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2) OR(__xor__INPUT_1, __xor__INPUT_2)
#define __xor__OR_1(__xor__INPUT_1, __xor__INPUT_2) OR(__xor__NOT_1(__xor__INPUT_1, __xor__INPUT_2), __xor__NOT_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__AND_1(__xor__INPUT_1, __xor__INPUT_2) AND(__xor__OR_1(__xor__INPUT_1, __xor__INPUT_2), __xor__OR_2(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2) OUTPUT(__xor__AND_1(__xor__INPUT_1, __xor__INPUT_2))
#define __xor__OUTPUT_2(__xor__INPUT_1, __xor__INPUT_2) OUTPUT(__xor__AND_1(__xor__INPUT_1, __xor__INPUT_2))
#define xor(__xor__INPUT_1, __xor__INPUT_2) __xor__OUTPUT_1(__xor__INPUT_1, __xor__INPUT_2), __xor__OUTPUT_2(__xor__INPUT_1, __xor__INPUT_2)
#define test_xor ((NTH_0(xor(0, 0)) == 0) && (NTH_1(xor(0, 0)) == 0) && (NTH_0(xor(1, 0)) == 1) && (NTH_1(xor(1, 0)) == 1) && (NTH_0(xor(0, 1)) == 1) && (NTH_1(xor(0, 1)) == 1) && (NTH_0(xor(1, 1)) == 0) && (NTH_1(xor(1, 1)) == 0))

#define test__all test_MAIN && test_xor

int main(void) {
	printf("tests:\n");
	printf("\tMAIN: %s\n", test_MAIN ? "passed" : "failed");
	printf("\txor: %s\n", test_xor ? "passed" : "failed");
	printf("%s\n", test__all ? "All tests passed" : "Some tests not OK");
	return 0;
}