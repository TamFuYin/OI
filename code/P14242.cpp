#include<bits/stdc++.h>
using ll=long long;
const int N=1e6+10;
using ll=long long;
int a[N];
ll s[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        s[n+1]=0;
        for(int i=n;i>=1;i--) s[i]=s[i+1]+a[i];
        std::sort(s+2,s+n+1);
        ll ans=s[1];
        printf("%lld ",ans);
        for(int i=n;i>=2;i--) ans+=s[i],printf("%lld ",ans);
        puts("");
    }
}