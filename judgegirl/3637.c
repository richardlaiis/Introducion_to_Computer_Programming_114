#include <stdio.h>
typedef unsigned long long ull;

int main() {
	ull N;
	scanf("%llu", &N);

	ull res = N;
	while (N) {
		N >>= 1;
		res ^= N;
	}

	printf("%llu\n", res);
}
