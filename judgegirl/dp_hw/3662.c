#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int curmask;
    int nxtmask;
} Frame;

static inline int isBusy(const char *sM, const char *sA, int r, int d) {
    return (r == 0 ? sM[d] : sA[d]) == '1';
}

static inline int freeNext(const char *sM, const char *sA, int d, int r) {
    return !isBusy(sM, sA, r, d);
}

static inline int okNext(const char *sM, const char *sA,
                         int d, int r, int nxtmask, int bit) {
    return freeNext(sM, sA, d, r) && !(nxtmask & bit);
}

static inline void push(Frame *st, int *sp, int c, int n) {
    st[*sp].curmask = c;
    st[*sp].nxtmask = n;
    (*sp)++;
}

ll solve(int N, int Mphase, ll MOD,
         const char *sM, const char *sA)
{
    ll dp[4] = {1, 0, 0, 0}, nxtdp[4] = {0};
    Frame st[64];

    for (int day = 0; day < N; day++) {
        nxtdp[0] = nxtdp[1] = nxtdp[2] = nxtdp[3] = 0;
        int hasNext = (day + 1 < N);

        for (int mask = 0; mask < 4; mask++) {
            ll ways = dp[mask];
            if (!ways) continue;

            int occM = (mask & 1) || isBusy(sM, sA, 0, day);
            int occA = (mask & 2) || isBusy(sM, sA, 1, day);

            int sp = 0;
            push(st, &sp, (occM ? 1 : 0) | (occA ? 2 : 0), 0);

            while (sp > 0) {
                Frame f = st[--sp];
                int cur = f.curmask;
                int nxt = f.nxtmask;

                if (cur == 3) {
                    nxtdp[nxt] = (nxtdp[nxt] + ways) % (MOD ? MOD : (ll)1e18);
                    continue;
                }

                int filledM = (cur & 1);
                int filledA = (cur & 2);

                if (!filledM) {
                    push(st, &sp, cur | 1, nxt);

                    if (hasNext && okNext(sM, sA, day + 1, 0, nxt, 1))
                        push(st, &sp, cur | 1, nxt | 1);

                    if (!filledA)
                        push(st, &sp, 3, nxt);

                    if (Mphase != 1) {  
                        if (hasNext && !filledA &&
                            okNext(sM, sA, day + 1, 1, nxt, 2))
                            push(st, &sp, 3, nxt | 2);

                        if (hasNext && !filledA &&
                            okNext(sM, sA, day + 1, 0, nxt, 1))
                            push(st, &sp, 3, nxt | 1);

                        if (hasNext &&
                            okNext(sM, sA, day + 1, 0, nxt, 1) &&
                            okNext(sM, sA, day + 1, 1, nxt, 2))
                            push(st, &sp, cur | 1, nxt | 3);
                    }
                } else {
                    push(st, &sp, 3, nxt);

                    if (hasNext && okNext(sM, sA, day + 1, 1, nxt, 2))
                        push(st, &sp, 3, nxt | 2);

                    if (Mphase != 1) {
                        if (hasNext &&
                            okNext(sM, sA, day + 1, 0, nxt, 1) &&
                            okNext(sM, sA, day + 1, 1, nxt, 2))
                            push(st, &sp, 3, nxt | 3);
                    }
                }
            }
        }

        memcpy(dp, nxtdp, sizeof(dp));
    }

    return MOD ? dp[0] % MOD : dp[0];
}

int main() {
    int N, M;
    ll MOD;
    if (scanf("%d %d %lld", &N, &M, &MOD) != 3) return 0;

    char *sM = malloc(N + 5);
    char *sA = malloc(N + 5);
    if (!sM || !sA) return 0;

    scanf("%s", sM);
    scanf("%s", sA);

    printf("%lld\n", solve(N, M, MOD, sM, sA));

    free(sM);
    free(sA);
    return 0;
}

