#include <stdio.h>
#include <stdlib.h>
#include <float.h>
int main() {
    int n, target;
    scanf("%d%d", &n, &target);
    short int* arr = (short int*)malloc(sizeof(short int) * (n+1));

    for (int i = 1; i <= n; i++) {
        scanf("%hd", arr+i);
    }

    int left = 1;
    double min_var = DBL_MAX;
    int anslen = 0;
    int found = 0;

    long long sum = 0;      /* current window sum */
    long long sqsum = 0;    /* current window squared-sum */

    for (int right = 1; right <= n; right++) {
        sum += arr[right];
        sqsum += (long long)arr[right] * arr[right];

        /* shrink while sum > target */
        while (left <= right && sum > target) {
            sum -= arr[left];
            sqsum -= (long long)arr[left] * arr[left];
            left++;
        }

        /* when equal, record all windows that end at `right` by moving left forward */
        while (left <= right && sum == target) {
            found = 1;
            double m = (double)(right - left + 1);
            double dsq = (double)sqsum;
            double dsum = (double)sum;
            double var = dsq / m - (dsum / m) * (dsum / m);
            if (var < min_var) {
                min_var = var;
                anslen = (int)m;
            } else if (var == min_var) {
                if ((int)m < anslen) anslen = (int)m;
            }

            sum -= arr[left];
            sqsum -= (long long)arr[left] * arr[left];
            left++;
        }
    }
    if (!found) {
        printf("0\n");
        return 0;
    }
    printf("%d %.6f\n", anslen, min_var);
    free(arr);
}