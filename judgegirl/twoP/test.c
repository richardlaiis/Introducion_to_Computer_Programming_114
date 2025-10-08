#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

typedef long long ll;

// coordinate compression comparator
int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}
int lower_bound(int *a, int n, int key) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (a[mid] < key) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    int n;
    if(scanf("%d",&n)!=1) return 0;

    int *h = malloc(sizeof(int)*n);
    int *c = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d",&h[i]);
    for(int i=0;i<n;i++) scanf("%d",&c[i]);

    ll L,R;
    scanf("%lld%lld",&L,&R);
    int P,K;
    scanf("%d%d",&P,&K);
    int Cmax,D;
    scanf("%d%d",&Cmax,&D);

    // coordinate compression
    int *vals = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) vals[i] = c[i];
    qsort(vals,n,sizeof(int),cmp_int);
    int m = 0;
    for(int i=0;i<n;i++) if(i==0||vals[i]!=vals[m-1]) vals[m++] = vals[i];
    for(int i=0;i<n;i++) c[i] = (uint16_t)lower_bound(vals,m,c[i]);
    free(vals);

    uint16_t *cntCat = calloc(m,sizeof(uint16_t));
    int distinct=0, peakCount=0;

    ll ans=0, sumh=0;
    int l=0, r_max=-1,r_low=0,r_high=0;

    // small deques to maintain max/min in current window
    int *qmax = malloc(sizeof(int)*n);
    int *qmin = malloc(sizeof(int)*n);
    int headmx=0, tailmx=0, headmn=0, tailmn=0;

    for(int lft=0;lft<n;lft++){
        if(r_max<lft-1) r_max=lft-1;

        while(r_max+1<n){
            int nxt = r_max+1;
            int ci = c[nxt];
            int newDistinct = distinct + (cntCat[ci]==0);
            int newPeak = peakCount + (h[nxt]>=P?1:0);

            int candMax = (tailmx==headmx)?h[nxt]:h[qmax[headmx]];
            int candMin = (tailmn==headmn)?h[nxt]:h[qmin[headmn]];
            if(tailmx>headmx && h[nxt]>candMax) candMax=h[nxt];
            if(tailmn>headmn && h[nxt]<candMin) candMin=h[nxt];

            if(newPeak>K || newDistinct>Cmax || (ll)candMax-(ll)candMin>D) break;

            if(cntCat[ci]==0) distinct++;
            cntCat[ci]++;
            if(h[nxt]>=P) peakCount++;

            while(tailmx>headmx && h[qmax[tailmx-1]]<=h[nxt]) tailmx--;
            qmax[tailmx++]=nxt;
            while(tailmn>headmn && h[qmin[tailmn-1]]>=h[nxt]) tailmn--;
            qmin[tailmn++]=nxt;

            sumh+=h[nxt];
            r_max++;
        }

        while(r_low<=r_max && sumh - (r_low>lft?0:0) < L) r_low++;
        while(r_high<=r_max && sumh - (r_low>lft?0:0) <= R) r_high++;

        if(r_low<=r_max){
            int right_bound=r_high-1;
            if(right_bound>r_max) right_bound=r_max;
            if(right_bound>=r_low) ans+=(ll)(right_bound - r_low +1);
        }

        if(r_max>=lft){
            int ci=c[lft];
            cntCat[ci]--;
            if(cntCat[ci]==0) distinct--;
            if(h[lft]>=P) peakCount--;
            if(tailmx>headmx && qmax[headmx]==lft) headmx++;
            if(tailmn>headmn && qmin[headmn]==lft) headmn++;
            sumh-=h[lft];
        }
    }

    printf("%lld\n",ans);

    free(h);
    free(c);
    free(cntCat);
    free(qmax);
    free(qmin);
    return 0;
}
