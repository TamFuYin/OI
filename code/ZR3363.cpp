#include<bits/stdc++.h>
struct Random {
  unsigned long long X;
  void init(unsigned long long seed) { X = seed; }
  unsigned long long Rand() {
    X ^= X << 13;
    X ^= X >> 7;
    X ^= X << 17;
    return X;
  }
}R;
const int N=1e5;
bool x[N];
int query(int p,int q){
    x[p]^=1;
}
int main(){
    int n,q,seed1,seed2,a,b;scanf("%d%d%d%d%d%d",&n,&q,&seed1,&seed2,&a,&b);
    R.init(seed1);
    for (int i = 1; i <= n; i++) x[i] = R.Rand() & 1;
    R.init(seed2);
    int ans=0;
    for (int i = 1; i <= q; i++) {
        int p = R.Rand() % n + 1, q = R.Rand() % n + 1;
        ans ^= query(p, q);
    }
    printf("%d\n",ans);
}