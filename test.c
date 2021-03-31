#include <stdio.h>

#define FIRST(A, ...) A
#define REST(A, ...) __VA_ARGS__

#define NTH_0(...) FIRST(__VA_ARGS__)
#define NTH_1(...) NTH_0(REST(__VA_ARGS__))
#define NTH_2(...) NTH_1(REST(__VA_ARGS__))
/* … */

#define NTH(N, ...) NTH_##N(__VA_ARGS__, unused)

int main(void) {
	printf("%d\n", NTH(2, 1, 2, 3));
	return 0;
}