#include<bits/stdc++.h>
using ll=long long;
std::priority_queue<std::pair<ll,int> > Q;
const int N=1e6+10,M=2e6+10;
ll dis[N];
int nx[M],ls[N],to[M],va[M],tot;
void add(int u,int v,int w){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
    va[tot]=w;
}
bool vis[N];
struct edge{int u,v;ll w;}e[M];
int fr[N];
int pa[N],sz[N];
int findp(int x){
    if(pa[x]==x) return x;
    return pa[x]=findp(pa[x]);
}
void merge(int x,int y){
    x=findp(x),y=findp(y);
    if(sz[x]<sz[y]) std::swap(x,y);
    sz[x]+=sz[y],pa[y]=x;
}
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++)
        scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    int k;scanf("%d",&k);
    std::fill(dis+1,dis+n+1,LLONG_MAX);
    for(int i=1,p;i<=k;i++) scanf("%d",&p),Q.emplace(dis[p]=0,fr[p]=p);
    while(!Q.empty()){
        int u=Q.top().second;Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=ls[u];i;i=nx[i]){
            if(dis[to[i]]>dis[u]+va[i]){
                dis[to[i]]=dis[u]+va[i];
                fr[to[i]]=fr[u];
                Q.emplace(-dis[to[i]],to[i]);
            }
        }
    }
    m=0;
    for(int u=1;u<=n;u++){
        for(int i=ls[u];i;i=nx[i]){
            if(to[i]>u){
                if(fr[u]!=fr[to[i]]){
                    e[++m]={fr[u],fr[to[i]],dis[u]+va[i]+dis[to[i]]};
                }
            }
        }
    }
    std::sort(e+1,e+m+1,[](const edge& u,const edge& v){return u.w<v.w;});
    std::iota(pa+1,pa+n+1,1);
    std::fill(sz+1,sz+n+1,1);
    ll ans=dis[1];
    for(int i=1;i<=m;i++)
        if(findp(e[i].u)!=findp(e[i].v))
            merge(e[i].u,e[i].v),ans+=e[i].w;
    printf("%lld",ans);
}