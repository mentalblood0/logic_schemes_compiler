#include <stdio.h>

#define NOT(x) (!(x))
#define OR(x, y) ((x) || (y))
#define AND(x, y) ((x) && (y))
#define OUTPUT(x) (x)

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_1(...) FIRST(__VA_ARGS__)

#define NTH_2(...) NTH_1(REST(__VA_ARGS__))
#define NTH_3(...) NTH_2(REST(__VA_ARGS__))


#define __AND_3__AND_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) AND(NTH_1(__AND_3__INPUT_1), NTH_1(__AND_3__INPUT_2))
#define __AND_3__AND_2(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) AND(NTH_1(__AND_3__AND_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)), NTH_1(__AND_3__INPUT_3))
#define __AND_3__OUTPUT_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) OUTPUT(NTH_1(__AND_3__AND_2(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)))
#define AND_3(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3) __AND_3__OUTPUT_1(__AND_3__INPUT_1, __AND_3__INPUT_2, __AND_3__INPUT_3)

#define __OR_3__OR_2(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OR(NTH_1(__OR_3__INPUT_1), NTH_1(__OR_3__INPUT_2))
#define __OR_3__OR_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OR(NTH_1(__OR_3__OR_2(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)), NTH_1(__OR_3__INPUT_3))
#define __OR_3__OUTPUT_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) OUTPUT(NTH_1(__OR_3__OR_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)))
#define OR_3(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3) __OR_3__OUTPUT_1(__OR_3__INPUT_1, __OR_3__INPUT_2, __OR_3__INPUT_3)

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
#define test_SUM__1__1 (NTH_1(SUM(0, 0, 0)) == 0)
#define test_SUM__1__2 (NTH_2(SUM(0, 0, 0)) == 0)
#define test_SUM__2__1 (NTH_1(SUM(0, 0, 1)) == 0)
#define test_SUM__2__2 (NTH_2(SUM(0, 0, 1)) == 1)
#define test_SUM__3__1 (NTH_1(SUM(0, 1, 0)) == 0)
#define test_SUM__3__2 (NTH_2(SUM(0, 1, 0)) == 1)
#define test_SUM__4__1 (NTH_1(SUM(0, 1, 1)) == 1)
#define test_SUM__4__2 (NTH_2(SUM(0, 1, 1)) == 0)
#define test_SUM__5__1 (NTH_1(SUM(1, 0, 0)) == 0)
#define test_SUM__5__2 (NTH_2(SUM(1, 0, 0)) == 1)
#define test_SUM__6__1 (NTH_1(SUM(1, 0, 1)) == 1)
#define test_SUM__6__2 (NTH_2(SUM(1, 0, 1)) == 0)
#define test_SUM__7__1 (NTH_1(SUM(1, 1, 0)) == 1)
#define test_SUM__7__2 (NTH_2(SUM(1, 1, 0)) == 0)
#define test_SUM__8__1 (NTH_1(SUM(1, 1, 1)) == 1)
#define test_SUM__8__2 (NTH_2(SUM(1, 1, 1)) == 1)
#define test_SUM__1 test_SUM__1__1 && test_SUM__1__2
#define test_SUM__2 test_SUM__2__1 && test_SUM__2__2
#define test_SUM__3 test_SUM__3__1 && test_SUM__3__2
#define test_SUM__4 test_SUM__4__1 && test_SUM__4__2
#define test_SUM__5 test_SUM__5__1 && test_SUM__5__2
#define test_SUM__6 test_SUM__6__1 && test_SUM__6__2
#define test_SUM__7 test_SUM__7__1 && test_SUM__7__2
#define test_SUM__8 test_SUM__8__1 && test_SUM__8__2
#define test_SUM test_SUM__1 && test_SUM__2 && test_SUM__3 && test_SUM__4 && test_SUM__5 && test_SUM__6 && test_SUM__7 && test_SUM__8

#define __MAIN__SUM_1(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) SUM(NTH_1(__MAIN__INPUT_5), NTH_1(__MAIN__INPUT_4), NTH_1(__MAIN__INPUT_2))
#define __MAIN__SUM_2(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) SUM(NTH_1(__MAIN__INPUT_3), NTH_1(__MAIN__INPUT_1), NTH_1(__MAIN__SUM_1(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5)))
#define __MAIN__OUTPUT_3(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) OUTPUT(NTH_2(__MAIN__SUM_1(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5)))
#define __MAIN__OUTPUT_2(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) OUTPUT(NTH_2(__MAIN__SUM_2(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5)))
#define __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) OUTPUT(NTH_1(__MAIN__SUM_2(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5)))
#define MAIN(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5) __MAIN__OUTPUT_1(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5), __MAIN__OUTPUT_2(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5), __MAIN__OUTPUT_3(__MAIN__INPUT_1, __MAIN__INPUT_2, __MAIN__INPUT_3, __MAIN__INPUT_4, __MAIN__INPUT_5)
#define test_MAIN__1__1 (NTH_1(MAIN(0, 0, 0, 0, 0)) == 0)
#define test_MAIN__1__2 (NTH_2(MAIN(0, 0, 0, 0, 0)) == 0)
#define test_MAIN__1__3 (NTH_3(MAIN(0, 0, 0, 0, 0)) == 0)
#define test_MAIN__2__1 (NTH_1(MAIN(0, 0, 0, 1, 0)) == 0)
#define test_MAIN__2__2 (NTH_2(MAIN(0, 0, 0, 1, 0)) == 1)
#define test_MAIN__2__3 (NTH_3(MAIN(0, 0, 0, 1, 0)) == 0)
#define test_MAIN__3__1 (NTH_1(MAIN(0, 1, 0, 0, 0)) == 0)
#define test_MAIN__3__2 (NTH_2(MAIN(0, 1, 0, 0, 0)) == 1)
#define test_MAIN__3__3 (NTH_3(MAIN(0, 1, 0, 0, 0)) == 0)
#define test_MAIN__4__1 (NTH_1(MAIN(0, 1, 0, 1, 0)) == 1)
#define test_MAIN__4__2 (NTH_2(MAIN(0, 1, 0, 1, 0)) == 0)
#define test_MAIN__4__3 (NTH_3(MAIN(0, 1, 0, 1, 0)) == 0)
#define test_MAIN__5__1 (NTH_1(MAIN(0, 0, 1, 0, 0)) == 1)
#define test_MAIN__5__2 (NTH_2(MAIN(0, 0, 1, 0, 0)) == 0)
#define test_MAIN__5__3 (NTH_3(MAIN(0, 0, 1, 0, 0)) == 0)
#define test_MAIN__6__1 (NTH_1(MAIN(1, 0, 0, 0, 0)) == 1)
#define test_MAIN__6__2 (NTH_2(MAIN(1, 0, 0, 0, 0)) == 0)
#define test_MAIN__6__3 (NTH_3(MAIN(1, 0, 0, 0, 0)) == 0)
#define test_MAIN__1 test_MAIN__1__1 && test_MAIN__1__2 && test_MAIN__1__3
#define test_MAIN__2 test_MAIN__2__1 && test_MAIN__2__2 && test_MAIN__2__3
#define test_MAIN__3 test_MAIN__3__1 && test_MAIN__3__2 && test_MAIN__3__3
#define test_MAIN__4 test_MAIN__4__1 && test_MAIN__4__2 && test_MAIN__4__3
#define test_MAIN__5 test_MAIN__5__1 && test_MAIN__5__2 && test_MAIN__5__3
#define test_MAIN__6 test_MAIN__6__1 && test_MAIN__6__2 && test_MAIN__6__3
#define test_MAIN test_MAIN__1 && test_MAIN__2 && test_MAIN__3 && test_MAIN__4 && test_MAIN__5 && test_MAIN__6

#define test__all test_SUM && test_MAIN

int main(void) {
	printf("tests:\n");
printf("\tSUM:\n");
printf("\t\t[0, 0, 0] => [0, 0] %s\n", test_SUM__1 ? "passed" : "failed");
printf("\t\t[0, 0, 1] => [0, 1] %s\n", test_SUM__2 ? "passed" : "failed");
printf("\t\t[0, 1, 0] => [0, 1] %s\n", test_SUM__3 ? "passed" : "failed");
printf("\t\t[0, 1, 1] => [1, 0] %s\n", test_SUM__4 ? "passed" : "failed");
printf("\t\t[1, 0, 0] => [0, 1] %s\n", test_SUM__5 ? "passed" : "failed");
printf("\t\t[1, 0, 1] => [1, 0] %s\n", test_SUM__6 ? "passed" : "failed");
printf("\t\t[1, 1, 0] => [1, 0] %s\n", test_SUM__7 ? "passed" : "failed");
printf("\t\t[1, 1, 1] => [1, 1] %s\n", test_SUM__8 ? "passed" : "failed");
printf("\tMAIN:\n");
printf("\t\t[0, 0, 0, 0, 0] => [0, 0, 0] %s\n", test_MAIN__1 ? "passed" : "failed");
printf("\t\t[0, 0, 0, 1, 0] => [0, 1, 0] %s\n", test_MAIN__2 ? "passed" : "failed");
printf("\t\t[0, 1, 0, 0, 0] => [0, 1, 0] %s\n", test_MAIN__3 ? "passed" : "failed");
printf("\t\t[0, 1, 0, 1, 0] => [1, 0, 0] %s\n", test_MAIN__4 ? "passed" : "failed");
printf("\t\t[0, 0, 1, 0, 0] => [1, 0, 0] %s\n", test_MAIN__5 ? "passed" : "failed");
printf("\t\t[1, 0, 0, 0, 0] => [1, 0, 0] %s\n", test_MAIN__6 ? "passed" : "failed");
	printf("%s\n", test__all ? "All tests passed" : "Some tests failed");
	return 0;
}