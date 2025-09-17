#include <stdio.h>
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	while (n--) {
		int op, p;
		scanf("%d%d", &op, &p);
		if (op == 1) {
			if ((1 << p) & m) printf("No\n");
			else printf("Yes\n");
		} else if (op == 2) {
			if ((1 << p) & m) printf("Yes\n");
			else printf("No\n");
		} else if (op == 3) {
			m &= ~(1 << p);
			printf("%d\n",m);
		} else {
			m |= (1 << p);
			printf("%d\n",m);
		}
	}
}
