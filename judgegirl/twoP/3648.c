#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    int *data;
    int head, tail;
} Deque;

void initDeque(Deque *dq, int n) {
    dq->data = (int *)malloc(sizeof(int) * n);
    dq->head = dq->tail = 0;
}
int dq_empty(Deque *dq) { return dq->head == dq->tail; }
int dq_front(Deque *dq) { return dq->data[dq->head]; }
int dq_back(Deque *dq) { return dq->data[dq->tail - 1]; }
void dq_popFront(Deque *dq) { dq->head++; }
void dq_popBack(Deque *dq) { dq->tail--; }
void dq_pushBack(Deque *dq, int x) { dq->data[dq->tail++] = x; }
void freeDeque(Deque *dq) { free(dq->data); }

int cmp_int(const void *a, const void *b){
    int x = *(const int*)a, y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
int lower_bound(int *a, int n, int key){
    int l = 0, r = n;
    while (l < r){
        int mid = (l + r) >> 1;
        if (a[mid] < key) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main(){
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *h = (int*)malloc(sizeof(int) * n);
    int *c = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", &h[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    ll L, R;
    scanf("%lld %lld", &L, &R);
    int P, K;
    scanf("%d %d", &P, &K);
    int Cmax, D;
    scanf("%d %d", &Cmax, &D);

    // coordinate compress c into [0..m-1]
    int *vals = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) vals[i] = c[i];
    qsort(vals, n, sizeof(int), cmp_int);
    int m = 0;
    for (int i = 0; i < n; i++){
        if (i == 0 || vals[i] != vals[m-1]) vals[m++] = vals[i];
    }
    for (int i = 0; i < n; i++){
        int id = lower_bound(vals, m, c[i]);
        c[i] = id; // overwrite with compressed id
    }
    free(vals);

    // We'll replace the prefix-sum array with running two-pointer sums
    // to save memory. Use rl_excl/rh_incl to track boundaries relative to l:
    // rl_excl = last index r where sum(h[l..r]) < L (can be l-1 meaning empty)
    // rh_incl = last index r where sum(h[l..r]) <= R (can be l-1 meaning empty)
    int rl_excl = -1, rh_incl = -1;
    ll sum_rl = 0, sum_rh = 0;

    int *cntCat = (int*)calloc(m, sizeof(int)); // counts for compressed ids
    int distinct = 0;
    int peakCount = 0;

    Deque maxdq, mindq;
    initDeque(&maxdq, n);
    initDeque(&mindq, n);

    ll ans = 0;
    int r_max = -1;

    for (int l = 0; l < n; l++){
        if (r_max < l - 1) r_max = l - 1;

        // expand r_max as far as constraints allow
        while (r_max + 1 < n){
            int nxt = r_max + 1;
            int ci = c[nxt];
            int newDistinct = distinct + (cntCat[ci] == 0);
            int newPeak = peakCount + (h[nxt] >= P ? 1 : 0);

            int candMax = dq_empty(&maxdq) ? h[nxt] : h[dq_front(&maxdq)];
            int candMin = dq_empty(&mindq) ? h[nxt] : h[dq_front(&mindq)];
            if (!dq_empty(&maxdq) && h[nxt] > candMax) candMax = h[nxt];
            if (!dq_empty(&mindq) && h[nxt] < candMin) candMin = h[nxt];

            if (newPeak > K || newDistinct > Cmax || (ll)candMax - (ll)candMin > D) break;

            // commit add
            if (cntCat[ci] == 0) distinct++;
            cntCat[ci]++;
            if (h[nxt] >= P) peakCount++;

            while (!dq_empty(&maxdq) && h[dq_back(&maxdq)] <= h[nxt]) dq_popBack(&maxdq);
            dq_pushBack(&maxdq, nxt);
            while (!dq_empty(&mindq) && h[dq_back(&mindq)] >= h[nxt]) dq_popBack(&mindq);
            dq_pushBack(&mindq, nxt);

            r_max++;
        }

        // adjust running sums when l increments
        if (l == 0) {
            // rl_excl/rh_incl already -1, sums 0
        } else {
            // if previous rl_excl covered at least the old l, subtract h[l-1]
            if (rl_excl >= l) sum_rl -= (ll)h[l-1];
            else { rl_excl = l - 1; sum_rl = 0; }
            if (rh_incl >= l) sum_rh -= (ll)h[l-1];
            else { rh_incl = l - 1; sum_rh = 0; }
        }

        // advance rl_excl to be the last index where sum(h[l..rl_excl]) < L
        while (rl_excl + 1 <= r_max && sum_rl + (ll)h[rl_excl + 1] < L) {
            rl_excl++;
            sum_rl += (ll)h[rl_excl];
        }
        // advance rh_incl to be the last index where sum(h[l..rh_incl]) <= R
        while (rh_incl + 1 <= r_max && sum_rh + (ll)h[rh_incl + 1] <= R) {
            rh_incl++;
            sum_rh += (ll)h[rh_incl];
        }

        int r_low = rl_excl + 1; // first index with sum >= L
        int right_bound = rh_incl; // last index with sum <= R
        if (r_low <= r_max) {
            if (right_bound > r_max) right_bound = r_max;
            if (right_bound >= r_low) ans += (ll)(right_bound - r_low + 1);
        }

        // remove left l from window if present
        if (r_max >= l){
            int ci = c[l];
            cntCat[ci]--;
            if (cntCat[ci] == 0) distinct--;
            if (h[l] >= P) peakCount--;
            if (!dq_empty(&maxdq) && dq_front(&maxdq) == l) dq_popFront(&maxdq);
            if (!dq_empty(&mindq) && dq_front(&mindq) == l) dq_popFront(&mindq);
        }
    }

    printf("%lld\n", ans);

    freeDeque(&maxdq);
    freeDeque(&mindq);
    free(cntCat);
    free(h);
    free(c);
    return 0;
}
