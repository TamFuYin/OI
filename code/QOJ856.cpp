#include<bits/stdc++.h>
const int N=1e6+10;
std::vector<int> to[N];
const int MOD=1e9+7;
int ans,k;
int powk1[N],invk;
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return ret;
}
int dfn[N],low[N],dfncnt;
int sta[N],top;
int bridge;
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int v:to[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=std::min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                int len=1;
                do len++;while(sta[top--]!=v);
                if(len==2) ++bridge;
                else ans=1ll*ans*(powk1[len]+((len&1?-1:1)*(k-1)+MOD)%MOD)%MOD*invk%MOD;
            }
        }
        else low[u]=std::min(low[u],dfn[v]);
    }
}
int main(){
    // freopen64(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d%d",&n,&m,&k);
        powk1[0]=1;for(int i=1;i<=n;i++) powk1[i]=1ll*powk1[i-1]*(k-1)%MOD;
        invk=qpow(k,MOD-2);
        for(int i=1;i<=n;i++) to[i].clear(),dfn[i]=0;
        for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),
        to[u].push_back(v),to[v].push_back(u);
        ans=k;top=0;dfncnt=0;bridge=0;
        tarjan(1);ans=1ll*ans*powk1[bridge]%MOD;
        printf("%d\n",ans);
    }
}