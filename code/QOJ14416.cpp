#include<bits/stdc++.h>
const int N=1e3;
int a[N];
std::vector<int> to[N];
int f[N][N],g[N][N];
int n;
int dfncnt,dfn[N];
void dfs(int u,int fa=0){
    dfn[u]=++dfncnt;
    for(int v:to[u]){
        if(v==fa) continue;
        dfs(v,u);
    }
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);dfncnt=0;
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),
        to[u].push_back(v),to[v].push_back(u);
        dfs(1);
        for(int i=1;i<=n;i++)
    }
}