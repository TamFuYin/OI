#include<bits/stdc++.h>
const int N=1e5+10;
int pa[N],sz[N];
int findp(int x){
    if(pa[x]==x) return x;
    return pa[x]=findp(pa[x]);
}
void merge(int x,int y){
    x=findp(x),y=findp(y);
    if(x==y) return;
    if(sz[x]<sz[y]) std::swap(x,y);
    sz[x]+=sz[y];pa[y]=x;
}
template<typename T>
void ckmin(T& a,T b){
    a=std::min(a,b);
}
std::vector<int> to[N];
const int K=300;
int s[N];
int dis[K][N];
std::queue<int> Q;
bool vis[N];
void BFS(int i){
    memset(vis,0,sizeof vis);
    memset(dis[i],0x3f,sizeof dis[0]);
    Q.push(s[i]);
    dis[i][s[i]]=0;
    vis[s[i]]=1;
    while(!Q.empty()){
        int u=Q.front();Q.pop();
        for(int v:to[u])
            if(!vis[v]) Q.push(v),vis[v]=1,dis[i][v]=dis[i][u]+1;
    }
}
int main(){
    int n,m,q;scanf("%d%d%d",&n,&m,&q);
    std::fill(sz,sz+n+1,1);
    std::iota(pa,pa+n+1,0);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        merge(u,v),
        to[u].push_back(v),
        to[v].push_back(u);
    }
    std::iota(s,s+n,1);
    std::mt19937 rnd(time(0));
    std::shuffle(s,s+n,rnd);
    for(int i=0;i<300&&i<n;i++) BFS(i);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        if(findp(x)!=findp(y)) puts("YES");
        else if(sz[findp(x)]<=2e4) puts("NO");
        else{
            int d=INT_MAX;
            for(int i=0;i<300&&i<n;i++) ckmin(d,dis[i][x]+dis[i][y]);
            puts(d>2e4?"YES":"NO");
        }
    }
}