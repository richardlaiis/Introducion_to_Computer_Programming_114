#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void charToBinary(char c, char *buf) {
    for (int i = 7; i >= 0; i--) {
        buf[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    buf[8] = '\0';
}

int main() {
    char pattern[16];   

	scanf("%s", &pattern);
    getchar();
	
	char tmp[500] = "";
	char buf[9];

	char text[2000000] = "";
	int pos = 0;

	char c;
	while ((c = getchar()) != EOF) {
		charToBinary(c, buf);
		for (int i = 0; i < 8; i++) {
			text[pos++] = buf[i];
		}
	}
	/* while (scanf("%s", &tmp) != EOF) { */
	/* 	/1* printf("%s\n", tmp); *1/ */
	/* 	int n = strlen(tmp); */
	/* 	for (int i = 0; i < n; i++) { */
	/* 		charToBinary(tmp[i], buf); */
	/* 		/1* printf("%s\n", buf); *1/ */
	/* 		strcat(text, buf); */
	/* 	} */
	/* } */
	/* printf("%s\n", text); */
	int m = strlen(pattern);
	int n = pos;
	int ans = 0;
	for (int i = 0 ; i < n-m+1; i++) {
		int same = 1;
		for (int j = i; j < i+m; j++) {
			if (pattern[j-i] != text[j]) {
				same = 0;
				break;
			}
		}
		if (same == 1) ans++;
	}
	
	printf("%d\n", ans);

}

