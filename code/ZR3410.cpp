#include<bits/stdc++.h>
const int N=2e5+10;
namespace flow{
    const int M=N*4;
    int to[M],ls[N],ca[M],nx[M],tot=1;
    void addedge(int u,int v,int c){
        nx[++tot]=ls[u];
        to[ls[u]=tot]=v;
        ca[tot]=c;
    }
    void add(int u,int v,int c){
        addedge(u,v,c);addedge(v,u,0);
    }
    int d[N],cur[N];
    bool bfs(int s,int t){
        memset(d,-1,sizeof(d));
        memcpy(cur,ls,sizeof(ls));
        std::queue<int> q;
        d[s]=0;q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=ls[u];i;i=nx[i]){
                int v=to[i];
                if(ca[i]>0&&d[v]==-1){
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[t]!=-1;
    }
    int dfs(int u,int t,int flow=1e9){
        if(u==t||flow==0) return flow;
        int ret=0;
        for(int& i=cur[u];i&&flow;i=nx[i]){
            int v=to[i];
            if(d[v]==d[u]+1&&ca[i]>0){
                int f=dfs(v,t,std::min(flow,ca[i]));
                if(f>0) ca[i]-=f,ca[i^1]+=f,ret+=f,flow-=f;
            }
        }
        return ret;
    }
    int dinic(int s,int t){
        int ret=0;
        while(bfs(s,t))
            ret+=dfs(s,t);
        return ret;
    }
}
std::vector<std::pair<int,int> > ans;
std::vector<int> to[N];
using namespace flow;
int front[N],back[N];
namespace dsu{
    int pa[N],sz[N];
    void clear(int n){
        std::fill(sz+1,sz+n+1,1);
        std::iota(pa+1,pa+n+1,1);
        std::iota(front+1,front+n+1,1);
        std::iota(back+1,back+n+1,1);
    }
    int findp(int x){
        return pa[x]==x?x:pa[x]=findp(pa[x]);
    }
    void merge(int x,int y){
        x=findp(x);y=findp(y);
        front[y]=front[x];
        back[x]=back[y];
        if(x==y) return;
        if(sz[x]<sz[y]) std::swap(x,y);
        pa[y]=x;sz[x]+=sz[y];
    }
}
std::vector<std::pair<int,int> > edges;
int ind[N];
int main(){
    freopen64("tree.in","r",stdin);
    freopen64("tree.out","w",stdout);
    int n;scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),add(u,n+v,1),
        edges.push_back({u,v});
    int s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++)
        add(s,i,1),add(n+i,t,1);
    int tmpans=n-1-dinic(s,t);
    // printf("%d\n",);
    dsu::clear(n);
    for(int u=1;u<=n;u++){
        for(int i=ls[u];i;i=nx[i]){
            int v=flow::to[i];
            if(v!=s&&ca[i]==0) dsu::merge(u,v-n);
        }
    }
    for(auto e:edges){
        int u=dsu::findp(e.first),v=dsu::findp(e.second);
        if(u!=v) ::to[u].push_back(v),++ind[v];
    }
    std::queue<int> q;
    for(int i=1;i<=n;i++)
        if(dsu::pa[i]==i&&ind[i]==0) q.push(i);
    int las=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(las) ans.push_back({back[las],front[u]});
        las=u;
        for(int v: ::to[u]){
            if(!--ind[v]) q.push(v);
        }
    }
    printf("%d\n",(int)ans.size());
    assert((int)ans.size()==tmpans);
    for(auto e:ans) printf("%d %d\n",e.first,e.second);
}