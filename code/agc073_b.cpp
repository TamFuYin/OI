#include<bits/stdc++.h>
const int N=1e5;
using ll=long long;
ll a[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%lld",a+i);
        ll ans=0;
        while(n>1){
            int m=1;
            ll k=*std::min_element(a+2,a+n+1)/a[1];
            ans+=a[1]*k;
            for(int i=2;i<=n;i++){
                a[i]-=a[1]*k;
                if(a[i]) a[++m]=a[i];
            }
            n=m;
            std::inplace_merge(a+1,a+2,a+n+1);
            for(int i=1;i<=n;i++) printf("%lld ",a[i]);puts("");
        }
        printf("%lld\n",ans);
    }
}