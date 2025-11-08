#include<bits/stdc++.h>
template<typename T>
T lowb(T x){return x&-x;}
#define lg std::__lg
#define popc __builtin_popcount
const int N=15,MOD=998244353;
using ll=long long;
ll a[N];
int Adj[N];
int E[1<<N];
ll mina[1<<N];//みな
int g[1<<N][2][2];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int eff(int x){
    return x&1?MOD-1:1;
}
int main(){
    freopen(".in","r",stdin);
    int n,m;ll c;scanf("%d%d%lld",&n,&m,&c);
    for(int i=0;i<n;i++) scanf("%lld",a+i);
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        --u,--v;
        Adj[u]|=1<<v;
        Adj[v]|=1<<u;
    }
    for(int s=1;s<(1<<n);s++) E[s]=E[s^lowb(s)]+popc(Adj[lg(lowb(s))]&s);
    mina[0]=INT_MAX;
    for(int s=1;s<(1<<n);s++) mina[s]=std::min(a[lg(lowb(s))],mina[s^lowb(s)]);
    int ans=0;
    // for(int d=std::__lg((ll)1e18);d>=0;d--){
    for(int d=1;d>=0;d--){
        memset(g,0,sizeof g);
        g[0][0][0]=qpow(2,MOD-1-d);
        int pd=(1ll<<d)%MOD;
        for(int s=1;s<(1<<n);s++){
            for(int j=0;j<=1;j++){
                for(int k=0;k<=1;k++){
                    for(int t=s;t;t=(t-1)&s)if(!(s^t)||lowb(t)<lowb(s^t)){
                        if(popc(t)&1^1){
                            (g[s][j][k]+=1ll*eff(E[t])*g[s^t][j][k]%MOD*(mina[t]+1)%MOD)%=MOD;
                            continue;
                        }
                        (g[s][j][k]+=1ll*eff(E[t])*g[s^t][j][k^(mina[t]>>d&1)]%MOD*((mina[t]&((1ll<<d)-1))+1)%MOD)%=MOD;
                        if(mina[t]>>d&1) (g[s][j|1][k]+=1ll*eff(E[t])*pd%MOD*g[s^t][j][k]%MOD)%=MOD;
                    }
                }
            }
        }
        (ans+=g[(1<<n)-1][1][c>>d&1])%=MOD;
        bool tot=0;
        for(int i=0;i<n;i++) tot^=a[i]>>d&1;
        if(!d&&(tot==(c&1))) (++ans)%=MOD;
        if(tot!=(c>>d&1)) break;
    }
    printf("%d",ans);
}