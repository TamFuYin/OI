#include<bits/stdc++.h>
const int N=1e5+10;
int to[N*2],ls[N],nx[N*2],tot;
void add(int u,int v){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
}
struct BIT{
    std::vector<int> t;
    void update(int p,int v){
        while(p){

        }
    }
}crs[N],in[N];
bool vis[N];int siz[N],sum,rt,RT;
void getG(int u,int fa=0){
    siz[u]=1;int mxs=0;
    for(int i=ls[u],v,tmp;i;i=nx[i]){
        if(!vis[v=to[i]]&&v!=fa){
            getG(v,u);
            siz[u]+=siz[v];
            mxs=std::max(mxs,siz[v]);
        }
    }
    mxs=std::max(mxs,sum-siz[u]);
    if(mxs<=sum/2) rt=u;
}
int fa[N];
void dfz(int u){
    vis[u]=1;
    for(int i=ls[u],v;i;i=nx[i]){
        if(!vis[v=to[i]]){
            sum=siz[v];
            getG(v);
            fa[rt]=u;
            dfz(rt);
        }
    }
}
const int F=log2(N)+2;
int dep[N],f[N][F];
int LCA(int x,int y){
    
}
int dist(int x,int y){
    return dep[x]+dep[y]-dep[LCA(x,y)];
}
void maintain(int x,int v){
    for(int rt=x;rt;rt=fa[rt]){
        in[rt].update(dist(x,rt),v);
        crs[rt].update(dist(x,fa[rt]),v);
    }
}
int main(){
    int n,m;scanf("%d%d",&n,&m);
    sum=n;getG(1);dfz(rt);
    for(int i=1,value;i<=n;i++) scanf("%d",&value),maintain(i,value);
}