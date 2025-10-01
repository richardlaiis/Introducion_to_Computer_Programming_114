#include <stdio.h>
typedef unsigned long long ull;

int main() {
	ull N,R;
	scanf("%llu%llu", &N, &R);
	
	ull res1 = N;
	while (N) {
		N >>= 1;
		res1 ^= N;
	}

	ull l = 1, r = res1;
	while (l <= r) {
		ull mid = (l + r)/2;
		if (mid & R != 0) {
			
		} else {
			l = mid;
		}
	}

}
