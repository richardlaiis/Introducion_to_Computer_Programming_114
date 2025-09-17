#include <stdio.h>
int main() {
	int b0,k;
	long long one = 1;
	scanf("%d%d",&b0,&k);
	for (int i = 0; i < k; i++) {
		long long q;
		scanf("%lld", &q);
		if (q == one) {
			printf("%d\n", b0);
			continue;
		}	
		/* printf("%d ",j); */
		int flip = 0;
		while (q > 1) {
			int j = 0;
			for (j = 0; j <= 50; j++) {
				if ((one << j) >= q) {
					break;
				}
			}
			q -= (one << (j-1));
			flip++;
		}
		/* printf("%d ", flip); */
		if (flip & 1) printf("%d\n", !b0);
		else printf("%d\n", b0);
	}
}
