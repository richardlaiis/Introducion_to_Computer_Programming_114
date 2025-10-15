#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int x = *(int*)a, y = *(int*)b;
    return (x > y) - (x < y);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    // Step 1: copy and sort to compress
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = arr[i];
    qsort(tmp, n, sizeof(int), cmp);

    // Step 2: remove duplicates
    int uniq = 0;
    for (int i = 1; i < n; i++)
        if (tmp[i] != tmp[uniq]) tmp[++uniq] = tmp[i];
    uniq++; // number of distinct values

    // Step 3: remap arr[i] → compressed index
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = uniq - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (tmp[mid] == arr[i]) {
                arr[i] = mid;
                break;
            } else if (tmp[mid] < arr[i])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    free(tmp);

    // Step 4: your logic, with compact idx
    int *idx = malloc(uniq * sizeof(int));
    for (int i = 0; i < uniq; i++) idx[i] = -1;

    int left = 0, ans = 0;
    for (int right = 0; right < n; right++) {
        while (idx[arr[right]] != -1 && left <= right) {
            idx[arr[left]] = -1;
            left++;
        }
        idx[arr[right]] = right;
        if (right - left + 1 == k) {
            ans++;
            idx[arr[left++]] = -1;
        }
    }

    printf("%d\n", ans);

    free(arr);
    free(idx);
}
