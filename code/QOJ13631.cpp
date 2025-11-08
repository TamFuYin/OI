#pragma GCC optimize(3)
#include<bits/stdc++.h>
const int N=2e6+10,lgN=log2(N)+1;
struct matrix{
    unsigned cov,covv,flp;
    matrix(){}
    matrix(int op,unsigned x){
        if(op==1) cov=~x,covv=flp=0;
        else if(op==2) cov=covv=x,flp=0;
        else cov=covv=0,flp=x;
    }
    matrix& operator*=(const matrix& b){
        cov|=b.cov;
        covv=b.covv|((covv^b.flp)&(cov^b.cov));
        flp=(flp^b.flp)&~cov;
        return *this;
    }
    bool empty()const{
        return !cov&&!flp;
    }
    void clear(){
        cov=covv=flp=0;
    }
}tag[N*4];
struct vector{
    unsigned x,nx;
    vector(unsigned x=0):x(x),nx(~x){}
    vector(unsigned x,unsigned nx):x(x),nx(nx){}
    vector operator+(const vector& b)const{
        return vector(x&b.x,nx&b.nx);
    }
    vector& operator*=(const matrix& b){
        return *this={(b.flp&nx)|(~(b.flp|b.cov)&x)|b.covv,
            (b.flp&x)|(~(b.flp|b.cov)&nx)|(~b.covv&b.cov)};
    }
}b[N],t[N*4];
int a[N],m;
namespace std{
    template<>
    struct hash<std::pair<int,int> >{
        size_t operator()(const pair<int,int>& p) const noexcept{
            return hash<int>()(p.first)^hash<int>()(p.second);
        }
    };
}
std::unordered_map<std::pair<int,int>,int> pto;
int sn[N][2];
int hs[N],hk[N],siz[N],fa[N];
int buildtree(int l,int r){
    int o=++m;pto[{l,r}]=o;
    if(l==r){
        b[o]=a[l];
        siz[o]=1;
        return o;
    }
    int mid;scanf("%d",&mid);
    sn[o][0]=buildtree(l,mid),sn[o][1]=buildtree(mid+1,r);
    siz[o]=siz[sn[o][0]]+siz[sn[o][1]]+1;
    hs[o]=sn[o][hk[o]=siz[sn[o][0]]<siz[sn[o][1]]];
    b[o]=b[sn[o][0]]+b[sn[o][1]];
    fa[sn[o][0]]=fa[sn[o][1]]=o;
    return o;
}
int top[N],dfn[N],rnk[N],bot[N],len[N][2];
void dfs(int u){
    rnk[dfn[u]=++dfn[0]]=u;
    if(!hs[u]) {bot[u]=u;return;}
    top[hs[u]]=top[u],dfs(hs[u]),bot[u]=bot[hs[u]];
    int v=sn[u][!hk[u]];top[v]=v,dfs(v);
    len[u][hk[u]]=len[hs[u]][hk[u]]+1;
}
void pushup(int o){
    t[o]=t[o<<1]+t[o<<1|1];
}
void build(int l=1,int r=m,int o=1){
    if(l==r){
        int p=rnk[l];
        if(bot[p]==p) t[o]=b[p];
        else t[o]=b[sn[p][!hk[p]]];
        return;
    }
    int mid=l+r>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
    pushup(o);
}
void pushdown(int o){
    if(!tag[o].empty()){
        t[o<<1]*=tag[o];
        tag[o<<1]*=tag[o];
        t[o<<1|1]*=tag[o];
        tag[o<<1|1]*=tag[o];
        tag[o].clear();
    }
}
void updsubtr(int L,int R,matrix A,int l=1,int r=m,int o=1){
    if(L<=l&&r<=R){
        t[o]*=A;
        tag[o]*=A;
        return;
    }
    int mid=l+r>>1;pushdown(o);
    if(L<=mid) updsubtr(L,R,A,l,mid,o<<1);
    if(mid<R) updsubtr(L,R,A,mid+1,r,o<<1|1);
    pushup(o);
}
vector query(int L,int R,int l=1,int r=m,int o=1){
    if(L>R) return {~0u,~0u};
    if(L<=l&&r<=R) return t[o];
    int mid=l+r>>1;pushdown(o);
    if(L<=mid&&mid<R) return query(L,R,l,mid,o<<1)+query(L,R,mid+1,r,o<<1|1);
    if(L<=mid) return query(L,R,l,mid,o<<1);
    assert(mid<R); return query(L,R,mid+1,r,o<<1|1);
}
void modify(int x,vector v,int l=1,int r=m,int o=1){
    if(l==r) {t[o]=v;return;}
    int mid=l+r>>1;pushdown(o);
    if(x<=mid) modify(x,v,l,mid,o<<1);
    else modify(x,v,mid+1,r,o<<1|1);
    pushup(o);
}
void updchain(int p){
    while(fa[p]){
        modify(dfn[fa[p]],query(dfn[p],dfn[bot[p]]));
        p=top[fa[p]];
    }
}
unsigned cur;int tmp;
int bisear(int L,int R,unsigned v,int l=1,int r=m,int o=1){
    if(L<=l&&r<=R){
        if((cur&t[o].x)!=v){cur&=t[o].x;return 0;}
        if(l==r&&(cur&t[o].x)==v) return l;
    }
    int mid=l+r>>1;pushdown(o);
    if(mid<R) if(tmp=bisear(L,R,v,mid+1,r,o<<1|1)) return tmp;
    if(L<=mid) return bisear(L,R,v,l,mid,o<<1);
    return 0;
}
#define TM(x) (__builtin_popcount(x)&1)
using ll=long long;
ll solve(int p){
    if(!p) return 0;
    unsigned v=query(dfn[p],dfn[bot[p]]).x;bool k=!TM(v);
    cur=query(dfn[p]+len[p][k]+1,dfn[bot[p]]).x;
    int q=rnk[bisear(dfn[p],dfn[p]+len[p][k],v)];
    // assert(query(dfn[q],dfn[bot[p]]).x==v);
    return solve(sn[q][k])+ll(dfn[q]-dfn[p]+1)*v;
}
int main(){
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    int n,q;scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    buildtree(1,n);dfs(top[1]=1);build();
    while(q--){
        int opt,l,r,x;scanf("%d%d%d",&opt,&l,&r);
        if(opt<=3){
            scanf("%d",&x);
            int p=pto[{l,r}];
            updsubtr(dfn[p],dfn[p]+siz[p]-1,matrix(opt,x));
            updchain(top[p]);
        }
        else printf("%lld\n",solve(pto[{l,r}]));
    }
}