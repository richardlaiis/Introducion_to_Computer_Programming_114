#include <stdio.h>
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int arr[10];
	int tmp[10];
	for (int i = 0; i < n; i++) {
		scanf("%d", arr+i);
		tmp[i] = arr[i];
		arr[i] &= ~(m);
	}

	int swapped = 0;
	for (int i = 0; i < n-1; i++) {
		swapped = 0;
		for (int j = 0; j < n-i-1; j++) {
			if ((arr[j] > arr[j+1]) || (arr[j]==arr[j+1] && tmp[j] > tmp[j+1])) {
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;

				t = tmp[j];
				tmp[j] = tmp[j+1];
				tmp[j+1] = t;
				swapped = 1;
			}
		}
		if (swapped == 0) {
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", tmp[i]);
	}
}
