#include<bits/stdc++.h>
const int N=2e6+10,MOD=998'244'353;
int fac[N+1],dfac[N+1],ifac[N+1],idfac[N+1];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int main(){
    fac[0]=1;
    for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);
    for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
    dfac[0]=1,dfac[1]=1;
    for(int i=2;i<=N;i++) dfac[i]=1ll*dfac[i-2]*i%MOD;
    idfac[N]=qpow(dfac[N],MOD-2),idfac[N-1]=qpow(idfac[N-1],MOD-2);
    for(int i=N;i>=2;i--) idfac[i-2]=1ll*idfac[i]*i%MOD;
    int n;scanf("%d",&n);
    auto f=[](int i,int j){
        return 1ll*(i==0?1:dfac[2*i-1])*(j==0?1:dfac[2*j-1])%MOD*fac[i+j]%MOD*idfac[2*(i+j)]%MOD*ifac[i]%MOD*ifac[j]%MOD;
    };
    int ans=0;
    for(int i=1,x;i<=n;i++) scanf("%d",&x),(ans+=1ll*x*f(i-1,n-i)%MOD)%=MOD;
    printf("%d",ans);
}