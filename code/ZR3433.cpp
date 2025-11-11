#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){
    a=std::min(a,b);
}
const int N=5e2+10;
using ll=long long;
int x[N];
ll f[N][N],g[N][N];
int main(){
    // freopen("time3.in","r",stdin);
    // freopen("time3.out","w",stdout);
    int n,h;scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++)
        scanf("%d",x+i),
        f[i][i]=0,g[i][i]=h;
    for(int l=n;l>=1;l--){
        for(int r=l+1;r<=n;r++){
            f[l][r]=LLONG_MAX;
            int y=h-(x[r]-x[l])/2;
            if(y>=0){
                for(int i=l;i<r;i++){
                    int lx=(x[l]+x[i]+1)/2,rx=(x[i+1]+x[r])/2,d=rx-lx-1;
                    ckmin(f[l][r],f[l][i]+f[i+1][r]+d);
                }
            }
            g[l][r]=f[l][r]+y;
            for(int i=l;i<r;i++)
                ckmin(g[l][r],g[l][i]+g[i+1][r]);
        }
    }
    ll ans=0;
    printf("%lld\n",g[1][n]);
}