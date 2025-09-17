#include <stdio.h>
#include <stdlib.h>

int bitCount(int x) {
	int cnt = 0;
	while (x) {
		cnt++;
		x >>= 1;
	}
	return cnt;
}

int max(int a, int b) {
	if (a > b) return a;
	return b;
}


int encode(int key, int doc) {
	int m = bitCount(key);
	int n = bitCount(doc);
	int t = max(m, n);
	int *c = (int *)malloc(t * sizeof(int));
	int *k = (int *)malloc(t * sizeof(int));
	int *d = (int *)malloc(t * sizeof(int));

	int tmp = key;
	for (int i = 0; i < t; i++) {
		k[i] = tmp%2;
		tmp >>= 1;
	}
	tmp = doc;
	for (int i = 0; i < t; i++) {
		d[i] = tmp%2;
		tmp >>= 1;
	}
	int diff = 0;
	for (int i = 0; i < t; i++) {
		diff += (k[i] != d[i]);
	}
	
	int o = bitCount(diff);
	tmp = diff;
	for (int i = 0; i < o; i++) {
		c[i] = tmp % 2;
		tmp >>= 1;
	}

	for (int i = o; i < t; i++) {
		c[i] = c[i % o];
	}

	int *e = (int *)malloc(t * sizeof(int));
	for (int i = 0; i < t; i++) {
		if (c[i] == 0) e[i] = k[i] ^ d[i];
		else e[i] = d[i];
	}
	int ans = diff;
	for (int i = t-1; i >= 0; i--) {
		ans = ans*10 + e[i];
	}
	return ans;
}


int main() {
	int key, doc;
	scanf("%d", &key);
	scanf("%d", &doc);
	printf("%d\n", encode(key, doc));
}
