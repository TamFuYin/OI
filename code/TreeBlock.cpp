#include<bits/stdc++.h>
const int N=1e5,S=100,D=N/S,FFF=20;
int nx[N*2],ls[N],to[N*2],tot;
void add(int u,int v){nx[++tot]=ls[u];to[ls[u]=tot]=v;}
int val[N],dep[N],id[N],fa[N][FFF],Fa[N];
std::bitset<N> bs[S][S];
int dfs(int u){
    int mxd=dep[u]=dep[fa[u][0]]+1;
    for(int i=1;i<FFF;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=ls[u];i;i=nx[i]){
        if(!dep[to[i]]){
            fa[to[i]][0]=u;
            mxd=std::max(mxd,dfs(to[i]));
        }
    }
    if(mxd-dep[u]>=D) {id[u]=++tot;mxd=dep[u];}
    return mxd;
}
int sta[N],top;
void dfs2(int u){
    for(int i=ls[u];i;i=nx[i]){
        if(dep[to[i]]==dep[u]+1){
            if(id[to[i]]){
                int ls=id[sta[top]],nx=id[to[i]];Fa[nx]=ls;
                for(int x=to[i];x!=sta[top];x=fa[x]) bs[ls][nx].set(val[x]);
                for(int j=1;j<top;j++) bs[id[sta[j]]][nx]=bs[id[sta[j]]][ls]|bs[ls][nx];
                sta[++top]=to[i];
                dfs2(to[i]);
                --top;
            }
            else dfs2(to[i]);
        }
    }
}
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    tot=0;dfs(1);if(!id[1]) id[1]=++tot;
    sta[top=1]=1;
}