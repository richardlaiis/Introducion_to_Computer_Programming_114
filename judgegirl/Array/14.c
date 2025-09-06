#include <stdio.h>
int main() {
	int n;
	int arr[1000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = n-1; i >= 0; i--) {
		printf("%d%c", arr[i], " \n"[i==0]);
	}
}
