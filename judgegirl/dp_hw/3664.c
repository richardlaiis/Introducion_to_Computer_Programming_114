#include <stdio.h>
#include <stdbool.h>

int n;

unsigned long long encode(int arr[]) {
	unsigned long long res = 0;
	for (int i = 0; i < n; i++) {
		res = (res << 3) | arr[i];
	}
	return res;
}

int dp[2100000] = {0};
int win(int arr[]) {
	unsigned long long idx = encode(arr);
	if (dp[idx] != 0) {
		return dp[idx];
	}
	if (arr[0] == 0) {
		dp[idx] = 1;
		return 1;
	}	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < arr[i]; j++) {
			int nxt[7];
			for (int k = 0; k < n; k++) {
				nxt[k] = arr[k];
			}
			for (int k = i; k < n; k++) {
				if (nxt[k] > j) nxt[k] = j;
			}
			if (win(nxt) == -1) {
				dp[idx] = 1;
				return 1;
			}
		}
	}
	dp[idx] = -1;
	return -1;
}

int main() {
	scanf("%d", &n);
	int a[7];
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	if (win(a) == 1) {
		printf("win\n");
	} else {
		printf("lose\n");
	}
}
