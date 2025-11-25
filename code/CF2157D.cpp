#include<bits/stdc++.h>
const int N=2e5+10;
template<typename T>
void ckmax(T& a,T b){
    a=std::max(a,b);
}
using ll=long long;
int a[N];
ll s[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,l,r;scanf("%d%d%d",&n,&l,&r);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        std::sort(a+1,a+n+1);
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
        ll ans=0;
        for(int k=-n;k<=n;k++){
            ll np=s[(n+k)/2],nm=(n^k)&1?s[n]-s[(n+k)/2+1]:s[n]-np,
            cost=np-nm;
            if(k>=0) ckmax(ans,(ll)k*l-cost);
            else ckmax(ans,(ll)k*r-cost);
        }
        printf("%lld\n",ans);
    }
}