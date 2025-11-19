#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

static int **dp;
static int **Cbin;
int nGlobal, cGlobal, mGlobal;

static inline int addmod(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

static inline int mulmod(long long a, long long b) {
    return (int)((a * b) % MOD);
}

int F(int n, int m) {
    if (n == 1) return (m == cGlobal) ? 1 : 0;
    if (m < cGlobal) return 0;

    int *row = dp[n];
    if (row[m] != -1) return row[m];

    int res = 0;
    int kmin = 2 * cGlobal - m;
    if (kmin < 0) kmin = 0;
    int kmax = cGlobal;

    for (int k = kmin; k <= kmax; k++) {
        int S2 = m - cGlobal + k;
        if (S2 < cGlobal) continue;

        int sub = F(n - 1, S2);
        if (sub == 0) continue;

        int ways = Cbin[cGlobal][k];
        res = addmod(res, mulmod(ways, sub));
    }

    row[m] = res;
    return res;
}

int main() {
    int t;
    scanf("%d", &t);

    /* Precompute binomial coefficients up to C = 102 */
    int CMAX = 105;
    Cbin = (int**)malloc((CMAX + 1) * sizeof(int*));
    for (int i = 0; i <= CMAX; i++) {
        Cbin[i] = (int*)malloc((CMAX + 1) * sizeof(int));
        for (int j = 0; j <= CMAX; j++) Cbin[i][j] = 0;
    }

    for (int i = 0; i <= CMAX; i++) {
        Cbin[i][0] = 1;
        Cbin[i][i] = 1;
        for (int j = 1; j < i; j++) {
            Cbin[i][j] = addmod(Cbin[i-1][j-1], Cbin[i-1][j]);
        }
    }

    while (t--) {
        int n, c, m;
        scanf("%d %d %d", &n, &c, &m);

        if (m < c || m > n * c) {
            printf("0\n");
            continue;
        }

        nGlobal = n;
        cGlobal = c;
        mGlobal = m;

        // build dp[n+1][m+1]
        dp = (int**)malloc((n + 1) * sizeof(int*));
        for (int i = 0; i <= n; i++) {
            dp[i] = (int*)malloc((m + 1) * sizeof(int));
            for (int j = 0; j <= m; j++) dp[i][j] = -1;
        }

        int ans = F(n, m);
        printf("%d\n", ans);

        for (int i = 0; i <= n; i++) free(dp[i]);
        free(dp);
    }

    for (int i = 0; i <= CMAX; i++) free(Cbin[i]);
    free(Cbin);

    return 0;
}

