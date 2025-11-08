#include<bits/stdc++.h>
namespace net{
    const int INF=1e9,N=1e5,M=1e5;
    int nx[M],ca[M],ls[N],to[M],tot=1;
    void addedge(int u,int v,int cap){
        nx[++tot]=ls[u];
        to[ls[u]=tot]=v;
        ca[tot]=cap;
    }
    void add(int u,int v,int cap){
        // printf("%d-(%d)>%d\n",u,cap,v);
        addedge(u,v,cap);
        addedge(v,u,0);
    }
    int S,T;int flow[N];
    void add(int u,int v,int low,int up){
        flow[u]-=low;
        flow[v]+=low;
        if(up-low>0) add(u,v,up-low);
    }
    int q[N],dep[N],cur[N];
    bool bfs(){
        memcpy(cur,ls,sizeof ls);
        memset(dep,0,sizeof dep);
        int head=0,tail=1;
        dep[q[1]=S]=1;
        while(head<tail){
            int u=q[++head];
            for(int i=ls[u];i;i=nx[i]){
                if(ca[i]&&!dep[to[i]]){
                    dep[to[i]]=dep[u]+1;
                    q[++tail]=to[i];
                }
            }
        }
        return dep[T];
    }
    int dfs(int u,int flow=INF){
        if(u==T) return flow;
        int ret=0;
        for(int &i=cur[u];i&&flow;i=nx[i])
        if(dep[to[i]]==dep[u]+1){
            int f=dfs(to[i],std::min(flow,ca[i]));
            ca[i]-=f;ca[i^1]+=f;flow-=f;ret+=f;
        }
        return ret;
    }
    int dinic(){
        int ret=0;
        while(bfs()) ret+=dfs(S);
        return ret;
    }
    int maxflow(int n,int s,int t){//let 's flow !!!
        add(t,s,0,INF);
        int ext=0;S=n+1,T=n+2;
        for(int i=1;i<=n;i++){
            if(flow[i]<0) add(i,T,-flow[i]);
            if(flow[i]>0) add(S,i,flow[i]),ext+=flow[i];
        }
        int f=dinic();
        printf("%d %d\n",f,ext);
        if(f<ext) return -1;
        S=s;T=t;return dinic();
    }
    void clear(){
        memset(ls,0,sizeof ls);tot=1;
        memset(flow,0,sizeof flow);
    }
}
int main(){
    freopen("input.in","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        net::clear();
        int s=n+m+1,t=s+1;
        for(int i=1,g;i<=m;i++) scanf("%d",&g),net::add(n+i,t,g,net::INF);
        for(int i=1,c,d,t,l,r;i<=n;i++){
            scanf("%d%d",&c,&d);
            net::add(s,i,0,d);
            while(c--){
                scanf("%d%d%d",&t,&l,&r);
                net::add(i,n+t+1,l,r);
            }
        }
        printf("%d\n\n",net::maxflow(n+m+2,s,t));
    }
}