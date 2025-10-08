#include <stdio.h>

int next_cube_sum(int x){
    int s = 0;
    if (x == 0) return 0;
    while (x){
        int d = x % 10;
        s += d*d*d;
        x /= 10;
    }
    return s;
}

int reaches_one(int x){
    if (x == 1) return 1;
    int slow = next_cube_sum(x);
    int fast = next_cube_sum(next_cube_sum(x));
    while (slow != fast){
        slow = next_cube_sum(slow);
        fast = next_cube_sum(next_cube_sum(fast));
    }
    return slow == 1;
}

int main(){
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--){
        int x;
        scanf("%d", &x);
        if (reaches_one(x)) printf("true\n");
        else printf("false\n");
    }
    return 0;
}
