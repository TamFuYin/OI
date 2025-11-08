#include<bits/stdc++.h>
const int MOD=998244353;
const int N=1e6+10;
std::vector<int> to[N];
void add(int u,int v){
    to[u].push_back(v);
    to[v].push_back(u);
}
bool vis[N];
int cnt_node,cnt_edge;
void dfs(int u){
    ++cnt_node;cnt_edge+=to[u].size();
    vis[u]=1;
    for(int v:to[u])if(!vis[v]) dfs(v);
}
int main(){
    // freopen("ex_tree4.in","r",stdin);
    // freopen("tree.out","w",stdout);
    int n;scanf("%d",&n);
    for(int i=1;i<=2*n-2;i++){
        int u,v;scanf("%d%d",&u,&v);
        if(u==v){
            puts("0");
            return 0;
        }
        if(u>v) std::swap(u,v);
        add(u,n-2+v);
    }
    int ans=1;
    for(int i=1;i<=2*n-2;i++)if(!vis[i]){
        cnt_node=cnt_edge=0;
        dfs(i);
        if(cnt_node*2!=cnt_edge) ans=0;//基环树的充要条件
        else ans=ans*2%MOD;
    }
    printf("%d",ans);
}