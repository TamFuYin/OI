#include<bits/stdc++.h>
const int N=1<<12;
int c[N];
int A[N][N];
int t[N];
const int MOD=1e9+7;
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int fac[N+1],ifac[N+1];
int binom(int n,int k){
    return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int main(){
    freopen("ex_guiltiness2.in","r",stdin);
    fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
    int n,m,X,Y;scanf("%d%d%d%d",&n,&m,&X,&Y);X^=Y;
    for(int i=1,b;i<=m;i++) scanf("%d",&b),++c[b];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",A[i]+j),A[i][j]^=Y;
    bool No=0;
    for(int i=1;i<=n;i++) if(A[i][i]!=0&&A[i][i]!=X) No=1;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(A[i][j]!=(A[1][i]^A[1][j])&&A[i][j]!=(A[1][i]^A[1][j]^X)) No=1;
    if(No){
        puts("0");
        return 0;
    }
    int ans=0;
    for(int a1=0;a1<N;a1++){
        std::fill(t,t+N,0);
        ++t[a1];
        for(int i=2;i<=n;i++) ++t[A[1][i]^a1];
        bool No=0;
        for(int i=0;i<N;i++) if(t[i]>c[i]) {No=1;break;}
        if(No) continue;
        int prod=1;
        if(X) for(int i=0;i<N;i++) if(i<(i^X)){
            int sum=0;
            for(int j=std::max(0,t[i]-c[i^X]);j<=t[i];j++)
                (sum+=binom(t[i],j))%=MOD;
            // if(sum!=1) printf("%d %d\n",i,sum);
            prod=1ll*prod*sum%MOD;
        }
        (ans+=prod)%=MOD;
    }
    printf("%d",ans);
}