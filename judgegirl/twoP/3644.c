#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *nums = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n + 1; i++) scanf("%d", &nums[i]);

    int slow = nums[0];
    int fast = nums[nums[0]];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    fast = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    printf("%d\n", slow);
    free(nums);
    return 0;
}
