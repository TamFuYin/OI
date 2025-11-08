#include<bits/stdc++.h>
template<typename T> void ckmax(T& a,T b){a=std::max(a,b);}
template<typename T> void ckmin(T& a,T b){a=std::min(a,b);}
const int N=2e5+10;
int n=2e5;
std::set<int> tags[N*4];
int t[N*4];
void pushdown(int o,int x){
    if(tags[o].find(x)!=tags[o].end()){
        tags[o<<1].insert(x);
        tags[o<<1|1].insert(x);
        ckmin(t[o<<1],x);
        ckmin(t[o<<1|1],x);
        tags[o].erase(x);
    }
}
int mintag(int o){
    return tags[o].empty()?INT_MAX:*tags[o].begin();
}
void pushup(int o){
    t[o]=std::min(std::max(t[o<<1],t[o<<1|1]),mintag(o));
}
void eraseTags(int L,int R,int x,int l=0,int r=n,int o=1){
    if(L<=l&&r<=R){
        tags[o].erase(x);
        if(l==r) t[o]=mintag(o);
        else pushup(o);
        return;
    }
    int mid=l+r>>1;pushdown(o,x);
    if(L<=mid) eraseTags(L,R,x,l,mid,o<<1);
    if(mid<R) eraseTags(L,R,x,mid+1,r,o<<1|1);
    pushup(o);
}
int getmax(int L,int R,int l=0,int r=n,int o=1){
    if(L<=l&&r<=R) return t[o];
    int mid=l+r>>1,ret=0;
    if(L<=mid) ckmax(ret,getmax(L,R,l,mid,o<<1));
    if(mid<R) ckmax(ret,getmax(L,R,mid+1,r,o<<1|1));
    return std::min(ret,mintag(o));
}
std::map<int,bool> odt[N];
void split(int l,int r,int x){
    auto L=--odt[x].upper_bound(l),R=odt[x].upper_bound(r);
    if(l!=L->first) odt[x].emplace(l,L->second);
    if(R==odt[x].end()||r+1!=R->first) odt[x].emplace(r+1,(--R)->second);
}
void assign(int l,int r,int x){
    split(l,r,x);
    for(auto i=odt[x].find(l);i!=odt[x].end()&&i->first!=r+1;){
        auto nx=std::next(i);
        if(i->second) eraseTags(i->first,nx==odt[x].end()?n:nx->first-1,x);
        odt[x].erase(i);
        i=nx;
    }
    odt[x].emplace(l,0);
}
int main(){
    // freopen("ex_mex4.in","r",stdin);
    // freopen("mex.out","w",stdout);
    using ll=long long;
    memset(t,0x3f,sizeof t);t[1]=0;
    for(int i=0;i<=n;i++) tags[1].insert(i);
    for(int i=0;i<=n;i++) odt[i].emplace(0,1);
    int q;scanf("%d",&q);
    ll S=0;while(q--){
        int op;scanf("%d",&op);
        ll x,l,r;int tmp=0;
        if(op==1) scanf("%lld",&x),x^=S;
        scanf("%lld%lld",&l,&r),l^=S,r^=S;
        if(op==1) assign(l,r,x);
        else printf("%d\n",tmp=getmax(l,r)),S+=tmp;
    }
}