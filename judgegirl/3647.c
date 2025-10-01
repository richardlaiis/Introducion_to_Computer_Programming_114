#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	int *x = (int *)a;
	int *y = (int *)b;
	if (*x > *y) return 1;
	else if (*x < *y) return -1;
	return 0;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int arr[200005];
	for (int i = 0; i < n; i++) {
		scanf("%d", arr+i);
	}
	qsort(arr, n, sizeof(int), cmp);
	/* for (int i = 0; i < n; i++) printf("%d\n", arr[i]); */

	long long ans = 0;
	int left = 0;
	int right = 1;
	
	while (left < n && right < n) {
		while (arr[right]-arr[left] > k && right-left >= 2) {
			left++;
		}
		if (right-left >= 2) {
			ans += 1LL * (right-left)*(right-left-1)/2;
		}
		right++;
	}

	printf("%lld\n", ans);
}
