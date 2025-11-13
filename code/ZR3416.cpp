#include<bits/stdc++.h>
int main(){
    // freopen("ex_gcd1.in","r",stdin);
    // freopen("ex_gcd1.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        using ll=long long;
        int n;ll m,k;scanf("%d%lld%lld",&n,&m,&k);
        ll x=(k-1)/(n-2),y=(k-1)%(n-2);
        for(int i=1;i<=y+1;i++) printf("%lld ",x+1);
        for(int i=y+2;i<=n;i++) printf("%lld ",x);
        puts("");
    }
}