#include<bits/stdc++.h>
const int N=2e3+10,MOD=998244353;
std::vector<int> to[N];
int f[N][N],g[N][N];
int ff[N],gg[N];
int siz[N];
void dfs(int u,int fa=0){
    siz[u]=1;
    f[u][1]=1;
    for(int v:to[u]){
        if(v==fa) continue;
        dfs(v,u);
        memset(ff,0,sizeof ff);
        memset(gg,0,sizeof gg);
        for(int i=0;i<=siz[u];i++){
            for(int j=0;j<=siz[v];j++){
                (ff[i+j]+=1ll*f[u][i]*f[v][j]%MOD)%=MOD;
                (gg[i+j]+=(1ll*f[u][i]*g[v][j]%MOD+1ll*g[u][i]*f[v][j]%MOD)%MOD)%=MOD;
            }
        }
        memcpy(f[u],ff,sizeof ff);
        memcpy(g[u],gg,sizeof gg);
        siz[u]+=siz[v];
    }
    for(int i=0;i<=siz[u];i++){
        (g[u][i]+=1ll*f[u][i]*(i-1)%MOD)%=MOD;
        (g[u][i]+=1ll*g[u][i+2]*(i+1)%MOD)%=MOD;
        (f[u][i]+=1ll*f[u][i+2]*(i+1)%MOD)%=MOD;
    }
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),to[u].push_back(v),to[v].push_back(u);
    dfs(1);
    printf("%d\n",int(1ll*g[1][0]*(MOD+1)/2%MOD));
}