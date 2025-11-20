#include<bits/stdc++.h>
const int N=1e5;
int nx[N],ls[N],to[N],va[N],tot;
void add(int u,int v,int w){
    to[++tot]=v,va[tot]=w,nx[tot]=ls[u],ls[u]=tot;
}
bool vis[N];
void dfs(int u){
    vis[u]=1;
    for(int i=ls[u];i;i=nx[i]){
        int v=to[i];
        if(vis[v]) continue;
        col[va[i]]=
        dfs(v);
    }
}
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),
    add(u,v,i),add(v,u,i);
    dfs(1);
}