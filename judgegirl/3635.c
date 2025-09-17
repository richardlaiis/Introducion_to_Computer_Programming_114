#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned long long ull;

int findP(ull x) {
	ull mask = (ull)((1 << 8) - 1);
	ull res = (mask << 56) & x;
	return (int)(res >> 56);
}

int cmp(const void *a, const void *b) {
	ull* x = (ull*)a;
	ull* y = (ull*)b;
	if (findP(*x) < findP(*y)) {
		return -1;
	} else {
		return 1;
	}
}

int main() {
	int N;
	scanf("%d", &N);
	
	ull nums[256];
	for (int i = 0; i < N; i++) {
		scanf("%llu", &nums[i]);
	}

	qsort(nums, N, sizeof(ull), cmp);
	
	char msg[3000] = "";
	for (int i = 0; i < N; i++) {
		char tmp[10];
		int idx = 0;
		for (int j = 6; j >= 0; j--) {
			ull mask = ((ull)255 << (j * 8));
			ull code = ((nums[i] & mask) >> (j*8));
			if (code != 0) {
				tmp[idx++] = (char)code;
			}
		}
		tmp[idx] = '\0';
		strcat(msg, tmp);
		/* printf("%s", tmp); */
	}
	/* printf("\n"); */
	printf("%s\n", msg);
}
