#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
const int N=2e5+10;
std::vector<int> C[N],T[N];
void addC(int u,int v){
    C[u].push_back(v),
    C[v].push_back(u);
}
void addT(int u,int v){
    T[u].push_back(v),
    T[v].push_back(u);
}
int n,m;
int dfn[N],low[N];
int sta[N],top;
bool insta[N];
void build(int u,int fa=0){
    insta[sta[++top]=u]=1;
    low[u]=dfn[u]=++dfn[0];
    for(int v:C[u]){
        if(v==fa) continue;
        if(!dfn[v]){
            build(v,u),addT(u,v);
            ckmin(low[u],low[v]);
        }
        else if(insta[v]){
            ckmin(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        addT(u,++m);
        do
        addT(m,sta[top]);
        while(sta[top--]!=u);
    }
}
int siz[N];
void getSiz(int u,int fa=0){
    siz[u]=u<=n;
    for(int v:T[u]){
        if(v==fa) continue;
        siz[u]+=siz[v];
    }
}
int main(){
    // freopen(".in","r",stdin);
    int testCase;scanf("%d",&testCase);
    while(testCase--){
        scanf("%d%d",&n,&m);
        for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),addC(u,v);
        m=n;top=0;dfn[0]=0;
        build(1);getSiz(1);
        int c=0;
        for(int u=n+1;u<=m;u++){
            int mx=0;
            for(int v:T[u])
                ckmax(mx,siz[v]>=siz[u]?n-siz[u]:siz[v]);
            if(mx<=n/2) assert(!c),c=u;
        }
        std::vector<int> ce;ce.clear();
        for(int u=1;u<=n;u++){
            int mx=0;
            for(int v:T[u])
                ckmax(mx,siz[v]>=siz[u]?n-siz[u]:siz[v]);
            if(mx<=n/2) ce.push_back(u);
        }
        if(c){
            std::sort(T[c].begin(),T[c].end());
            assert(T[c]==ce);
        }
        else{
            assert(ce.size()<=2);
        }
        for(int i=1;i<=n;i++) C[i].clear();
        for(int i=1;i<=m;i++) T[i].clear();
        std::fill(dfn+1,dfn+n+1,0);
    }
}