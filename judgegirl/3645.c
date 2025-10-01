#include <stdio.h>
#include <stdbool.h>

bool hasLoop(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		int slow = i, fast = i;
		int dir = arr[slow] > 0;
		
		
		int nslow = ((slow + arr[slow])%n + n) % n;
		bool tmp = (arr[nslow] > 0) != dir || nslow == slow; 
		nslow = ((nslow + arr[nslow])%n + n) % n;
		if (nslow == slow && !tmp) return true;
		
		while (1) {
			int nslow = ((slow + arr[slow])%n + n) % n;
			if ((arr[nslow] > 0) != dir || nslow == slow) break;
			int nfast = ((fast + arr[fast])%n + n) % n;
			if ((arr[nfast] > 0) != dir || nfast == fast) break;
			nfast = ((nfast + arr[nfast])%n + n) % n;
			if ((arr[nfast] > 0) != dir || nfast == fast) break;

			slow = nslow;
			fast = nfast;
			if (slow == fast) return true;
		}
	}
	return false;
}


int main() {
	int n;
	int arr[5000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	if (hasLoop(arr, n)) {
		printf("true\n");
	} else {
		printf("false\n");
	}
}
