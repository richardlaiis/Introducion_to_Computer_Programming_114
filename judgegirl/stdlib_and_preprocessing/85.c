#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int y, m, d;
} Date;

int cmp(const void *a, const void *b) {
	Date *ptr1 = (Date *)a;
	Date *ptr2 = (Date *)b;
	if (ptr1->y < ptr2->y) {
		return -1;
	} else if (ptr1->y > ptr2->y) {
		return 1;
	} else if (ptr1->m < ptr2->m) {
		return -1;
	} else if (ptr1->m > ptr2->m) {
		return 1;
	} else if (ptr1->d < ptr2->d) {
		return -1;
	} else if (ptr1->d > ptr2->d) {
		return 1;
	}
	return 0;
}

int main(void) {
	int n;
	scanf("%d", &n);
	Date* arr = (Date *)malloc(n * sizeof(Date));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &(arr[i].y), &(arr[i].m), &(arr[i].d));
	}
	qsort(arr, n, sizeof(Date), cmp);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", arr[i].y, arr[i].m, arr[i].d);
	}
}
