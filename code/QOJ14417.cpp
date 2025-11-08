#include<bits/stdc++.h>
std::map<std::string,int> mp;
const int N=1e5,lgN=20;
int p[N],v[N],a[N];
std::pair<int,int> st[N][lgN];
int getmax(int l,int r){
    int k=std::__lg(r-l+1);
    return -std::max(st[l][k],st[r-(1<<k)+1][k]).second;
}
int t[N];
int f[N][lgN];
int dep[N];
void make(int l,int r,int fa=0){
    if(l>r) return;
    int u=getmax(l,r);
    t[u]=-t[fa];
    dep[u]=dep[fa]+1;
    f[u][0]=fa;
    for(int i=1;i<lgN;i++) f[u][i]=f[f[u][i-1]][i-1];
    make(l,u-1,u);
    make(u+1,r,u);
}
int LCA(int u,int v){
    if(dep[u]<dep[v]) std::swap(u,v);
    int d=dep[u]-dep[v];
    for(int i=0;i<lgN;i++) if(d>>i&1) u=f[u][i];
    if(u==v) return u;
    for(int i=lgN-1;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
    return f[u][0];
}
using ll=long long;
ll pfs[N];
int main(){
    freopen64(".in","r",stdin);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int m,n,q;std::cin>>m>>n>>q;
    for(int i=1;i<=m;i++){
        std::string s;
        std::cin>>p[i]>>v[i]>>s;
        mp[s]=i;
    }
    for(int i=1;i<=n;i++){
        std::string s;
        std::cin>>s;
        a[i]=mp[s];
    }
    for(int i=1;i<=n;i++) st[i][0]={p[a[i]],-i};
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=std::max(st[i][j-1],st[i+(1<<j-1)][j-1]);
    t[0]=-1;
    make(1,n);
    for(int i=1;i<=n;i++) pfs[i]=pfs[i-1]+v[a[i]]*t[i];
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",(pfs[r]-pfs[l-1])*t[LCA(l,r)]);
    }
}