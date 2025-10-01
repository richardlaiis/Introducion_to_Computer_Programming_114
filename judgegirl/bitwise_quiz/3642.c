#include <stdio.h>
#include <stdint.h>

int initial_bit, not_bit, N, k;
int ops[55]; 

int control_bit(long long idx) {
    int cnt = __builtin_popcountll(idx); 
    int val = cnt & 1;                  
    return val ^ not_bit;                
}

int apply_op(int a, int b, int op) {
    if (op == 1) return a & b;
    if (op == 2) return a | b;
    return a ^ b;
}

int solve(int level, long long q) {
    if (level == 0) return initial_bit; 

    long long half = 1LL << (level - 1);

    if (q <= half) {
        return solve(level - 1, q);
    } else {
        int left_val = solve(level - 1, q - half);
        int ctrl = control_bit(q - half - 1); 
        return apply_op(left_val, ctrl, ops[level]);
    }
}

int main() {
    scanf("%d %d %d %d", &initial_bit, &not_bit, &N, &k);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &ops[i]);
    }

    while (k--) {
        long long q;
        scanf("%lld", &q);
        printf("%d\n", solve(N, q));
    }

    return 0;
}
