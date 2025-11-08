#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int N=4e5+10;
using ll=long long;
int a[N];ll f[N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    std::fill(f+1,f+n+1,LLONG_MAX);
    f[1]=0;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j&&i-j<=n/a[i];j--){
            ckmin(f[i],f[j]+1ll*a[i]*(i-j)*(i-j));
            if(a[j]<=a[i]) break;
        }
        for(int j=i+1;j<=n&&j-i<=n/a[i];j++){
            ckmin(f[j],f[i]+1ll*a[i]*(j-i)*(j-i));
            if(a[j]<=a[i]) break;
        }
    }
    for(int i=1;i<=n;i++) printf("%lld ",f[i]);
}