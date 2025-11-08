#include<bits/stdc++.h>
const int N=3e5+10,lgN=20;
using ll=long long;
int c[N];
std::vector<int> to[N];
int f[N][lgN];
ll g[N][lgN];
struct pair{
    int min,sec;
    void ck(int x){
        if(x<min) sec=min,min=x;
        else if(x<sec) sec=x;
    }
};
int dep[N];
void dfs(int u){
    pair p;p.min=p.sec=1e9;
    for(int v:to[u]){
        if(v==f[u][0]) continue;
        f[v][0]=u;
        dep[v]=dep[u]+1;
        dfs(v);
        p.ck(c[v]);
    }
    c[u]=std::min(c[u],p.min+p.sec);
    for(int v:to[u]){
        if(v==f[u][0]) continue;
        if(c[v]==p.min) g[v][0]=p.sec;
        else g[v][0]=p.min;
    }
}
void dfs2(int u){
    for(int i=1;i<lgN;i++)
        f[u][i]=f[f[u][i-1]][i-1],
        g[u][i]=g[u][i-1]+g[f[u][i-1]][i-1];
    for(int v:to[u]){
        if(v==f[u][0]) continue;
        dfs2(v);
    }
}
int main(){
    freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",c+i);
        for(int i=1;i<=n;i++) to[i].clear();
        for(int i=1,u,v;i<n;i++)
            scanf("%d%d",&u,&v),to[u].push_back(v),to[v].push_back(u);
        dfs(1);
        dfs2(1);
        while(m--){
            int x,y;scanf("%d%d",&x,&y);
            if(dep[x]<dep[y]){
                puts("-1");
                continue;
            }
            int d=dep[x]-dep[y];
            ll ans=0;
            for(int i=0;i<lgN;i++)
                if(d>>i&1){
                    ans+=g[x][i];
                    x=f[x][i];
                }
            if(x==y) printf("%lld\n",ans);
            else puts("-1");
        }
    }
}