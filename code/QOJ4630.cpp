#include<bits/stdc++.h>
namespace flow{
    const int N=1e5+10,M=1e6;
    int nx[M],ls[N],to[M],va[M],ca[M],tot=1;
    void addhalf(int u,int v,int c,int w){
        nx[++tot]=ls[u];
        to[ls[u]=tot]=v;
        va[tot]=w;ca[tot]=c;
    }
    void add(int u,int v,int c,int w){
        addhalf(u,v,c,w);
        addhalf(v,u,0,-w);
    }
    int h[N];
    bool vis[N];
    int dis[N];
    int s,t,n;
    const int INF=1e9;
    bool dijkstra(){
        std::priority_queue<std::pair<int,int> > Q;
        std::fill(dis+1,dis+n+1,INF);
        std::fill(vis+1,vis+n+1,0);
        Q.emplace(dis[s]=0,s);
        while(!Q.empty()){
            int u=Q.top().second;Q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=ls[u],v;i;i=nx[i]){
                int w=va[i]+h[u]-h[v=to[i]];
                if(ca[i]&&dis[v]>dis[u]+w&&!vis[v])
                    dis[v]=dis[u]+w,Q.emplace(-dis[v],v);
            }
        }
        for(int i=1;i<=n;i++) h[i]+=dis[i];
        return h[s]>h[t];
    }
    int dep[N];
    bool bfs(){
        std::queue<int> Q;
        std::fill(dep+1,dep+n+1,0);
        dep[s]=1;Q.push(s);
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            for(int i=ls[u],v;i;i=nx[i]){
                if(ca[i]&&va[i]+h[u]-h[v=to[i]]==0&&!dep[v]){
                    dep[v]=dep[u]+1;
                    Q.push(v);
                }
            }
        }
        return dep[t];
    }
    int cur[N];
    int dfs(int u=s,int fl=INF){
        if(u==t) return fl;
        int ret=0;
        for(int& i=cur[u],v;i&&fl;i=nx[i])
        if(ca[i]&&va[i]+h[u]-h[v=to[i]]==0&&dep[v]==dep[u]+1){
            int f=dfs(v,std::min(ca[i],fl));
            fl-=f,ret+=f;ca[i]-=f,ca[i^1]+=f;
        }
        return ret;
    }
    int maxf,minc,ans[N];
    void solve(){
        maxf=minc=0;
        while(dijkstra()) while(bfs()){
            std::copy(ls+1,ls+n+1,cur+1);
            int f=dfs(),v=h[t]-h[s];
            // printf(">> %d %d\n",f,v);
            for(int i=maxf+1;i<=maxf+f;i++) ans[i]=ans[i-1]+v;
            maxf+=f;minc+=f*v;
        }
    }
}
using namespace flow;
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),add(u,n+v,1,-w);
    s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++) add(s,i,1,0),add(n+i,t,1,0);
    flow::n=2*n+2;
    h[s]=5;std::fill(h+1,h+n+1,5);
    //初始化势能函数，使任意边 va[i]+h[u]-h[v]>=0
    solve();
    for(int i=1,cur=0;i<=n;i++){
        cur=std::max(cur,-ans[i]);
        printf("%d\n",cur);
    }
}
/*
input:
2 3
1 1 4
1 2 2
2 1 3
output:
4
5
my output:
0
0

why?
*/