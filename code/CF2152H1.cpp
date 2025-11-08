#include<bits/stdc++.h>
const int N=5e5+10;
using ll=long long;
int nx[N],to[N],ls[N],va[N],tot;
void add(int u,int v,int w){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
    va[tot]=w;
}
ll f[N],a[N];
int l;
void dfs(int u,int fa=0,int fe=0){
    f[u]=0;
    for(int i=ls[u],v;i;i=nx[i]){
        if((v=to[i])==fa) continue;
        dfs(v,u,va[i]);
        f[u]+=std::min((ll)va[i],f[v]);
    }
    a[u]=std::max(0ll,l-fe-f[u]);
    f[u]+=a[u];
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        std::fill(ls+1,ls+n+1,0);tot=0;
        for(int i=1,u,v,w;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);add(v,u,w);
        }
        int q;scanf("%d",&q);
        while(q--){
            scanf("%d",&l);
            dfs(1);
            ll ans=0;
            for(int i=1;i<=n;i++) ans+=a[i];
            printf("%lld\n",ans);
        }
    }
}