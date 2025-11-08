#include<bits/stdc++.h>
const int N=2e5+10;
using ll=long long;
ll d[N];
int main(){
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    int min=2e9,mod=a+b;
    for(int i=1;i<=n;i++)
        scanf("%lld",&d[i]),d[i]%=mod;
    std::sort(d+1,d+n+1);
    n=std::unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)
        min=std::min(min,int((d[i]-d[i%n+1]+mod)%mod));
    printf(min<a?"Yes":"No");
}