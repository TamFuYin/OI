#include<bits/stdc++.h>
const int N=5e3+10,MOD=998244353;
// int qpow(int a,int b){
//     int ret=1;
//     while(b){
//         if(b&1) ret=1ll*ret*a%MOD;
//         a=1ll*a*a%MOD;b>>=1;
//     }
//     return ret;
// }
// int fac[N+1],ifac[N+1];
// int binom(int n,int k){
//     return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
// }
int g[N+1][N+1],h[N+1][N+1];
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    freopen("waaadreamer.in","r",stdin);
    freopen("waaadreamer.out","w",stdout);
    // fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    // ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
    for(int s=1;s<=2*N;s++){
        for(int n=std::max(1,s-N);n<=s&&n<=N;n++){
            int m=s-n;
            g[n][m]=(1ll*n*(1+g[m][n-1])%MOD+2*h[n-1][m]%MOD)%MOD;
            h[n][m]=(h[n-1][m]+g[n][m])%MOD;
        }
    }
    // for(int n=0;n<N;n++){
    //     for(int m=0;m<N;m++){
    //         printf("%d ",g[n][m]);
    //     }
    //     puts("");
    // }
    // for(int n=1;n<=100;n++,puts(""))
        // for(int m=1;m<=100;m++) printf("%d ",g[n][m]);
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        // int ans=0;
        // for(int i=1;i<=n;i++)
        //     for(int j=0;j<=m;j++)
        //         (ans+=1ll*(g[i][j]+g[j][i])*binom(n,i)%MOD*binom(m,j)%MOD)%=MOD;
        printf("%d\n",(g[n][m]+g[m][n])%MOD);
    }
}
