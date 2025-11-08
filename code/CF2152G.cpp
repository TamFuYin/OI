#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=1e5+10;
int a[N];
std::vector<int> to[N];
int dfn[N],rnk[N],fa[N],siz[N],son[N],top[N];
void dfs1(int u){
    siz[u]=1;
    for(int v:to[u]) if(v!=fa[u]){
        fa[v]=u;dfs1(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int Top=1){
    top[rnk[dfn[u]=++dfn[0]]=u]=Top;
    if(son[u]) dfs2(son[u],Top);
    for(int v:to[u]) if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
}
int t[N*4];
int n;
void build(int l=1,int r=n,int o=1){
    if(l==r){
        t[o]=a[rnk[l]]?l:0;
        return;
    }
    int m=l+r>>1;
    build(l,m,o<<1);
    build(m+1,r,o<<1|1);
    t[o]=std::max(t[o<<1],t[o<<1|1]);
}
void modify(int x,int l=1,int r=n,int o=1){
    if(l==r){
        t[o]=a[rnk[l]]?l:0;
        return;
    }
    int m=l+r>>1;
    if(x<=m) modify(x,l,m,o<<1);
    else modify(x,m+1,r,o<<1|1);
    t[o]=std::max(t[o<<1],t[o<<1|1]);
}
int getmax(int L,int R,int l=1,int r=n,int o=1){
    if(L>R) return 0;
    if(L<=l&&r<=R) return t[o];
    int m=l+r>>1;int ret=0;
    if(L<=m) ckmax(ret,getmax(L,R,l,m,o<<1));
    if(m<R) ckmax(ret,getmax(L,R,m+1,r,o<<1|1));
    return ret;
}
int b[N];
int ans;
void update(int x){
    if(!x) return;
    int p=b[x];b[x]=!getmax(dfn[x]+1,dfn[x]+siz[x]-1);
    ans+=b[x]-p;
}
int findlas(int x){
    x=fa[x];
    while(x){
        int p=getmax(dfn[top[x]],dfn[x]);
        if(p) return rnk[p];
        x=fa[top[x]];
    }
    return 0;
}
int main(){
    freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);dfn[0]=0;
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        for(int i=1;i<=n;i++) to[i].clear();
        for(int i=1,u,v;i<n;i++){
            scanf("%d%d",&u,&v);
            to[u].push_back(v);
            to[v].push_back(u);
        }
        dfs1(1);dfs2(1);build();
        ans=0;std::fill(b+1,b+n+1,0);
        for(int i=1;i<=n;i++) if(a[i]) update(i);
        printf("%d\n",ans);
        int q;scanf("%d",&q);
        while(q--){
            int v;scanf("%d",&v);
            if(a[v]){
                a[v]=0;
                modify(dfn[v]);
                update(findlas(v));
                ans-=b[v];b[v]=0;
            }
            else{
                a[v]=1;
                modify(dfn[v]);
                update(v);
                update(findlas(v));
            }
            printf("%d\n",ans);
        }
    }
}