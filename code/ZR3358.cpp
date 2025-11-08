#include<bits/stdc++.h>
using ll=long long;
const int V=1e6;
template<typename T>
void clamp(T& x,T lo,T hi){
    if(x<lo) x=lo;
    if(hi<x) x=hi;
}
const int S=1e6;
struct func{//维护凸函数的差分 f'(x)=f(x)-f(x-1)
    struct vector{
        int x;
        ll y;
        vector operator+(const vector &b)const{
            return {x+b.x,y+b.y};
        }
        vector left()const{
            return {(x+1)/2,0};
        }
        vector right()const{
            return {x/2,0};
        }
    }begin,t[S];
    ll mx[S];// max f'(x) in [l,r]
    ll tag[S];
    int ls[S],rs[S],size;
    void pushup(int o){
        mx[o]=mx[rs[o]];
        // assert(ls[o]&&rs[o]);
        t[o]=t[ls[o]]+t[rs[o]];
    }
    void expand(int o){
        if(!ls[o]){
            t[ls[o]=++size]=t[o].left();
            t[rs[o]=++size]=t[o].right();
        }
    }
    void push(int& o,ll v){
        tag[o]+=v,
        mx[o]+=v,
        t[o].y+=t[o].x*v;
    }
    void pushdown(int o){
        expand(o);
        if(tag[o]){
            push(ls[o],tag[o]);
            push(rs[o],tag[o]);
            tag[o]=0;
        }
    }
    void add(int L,int R,int v,int l=-V,int r=V,int o=1){
        if(L<=l&&r<=R) return push(o,v);
        int mid=l+(r-l)/2;pushdown(o);
        if(L<=mid) add(L,R,v,l,mid,ls[o]);
        if(mid<R) add(L,R,v,mid+1,r,rs[o]);
        pushup(o);
    }
    vector find_rec(ll k,int l=-V,int r=V,int o=1){
        if(l==r) return mx[o]<=k?t[o]:vector{0,0};
        int mid=l+(r-l)/2;pushdown(o);
        if(mx[ls[o]]<=k) return t[ls[o]]+find_rec(k,mid+1,r,rs[o]);
        else return find_rec(k,l,mid,ls[o]);
    }
    vector find(ll k){//f'(x)\le k 的最大位置
        return begin+find_rec(k);
    }
    ll getsum(int L,int R,int l=-V,int r=V,int o=1){
        if(L<=l&&r<=R) return t[o].y;
        int mid=l+(r-l)/2;ll ret=0;pushdown(o);
        if(L<=mid) ret+=getsum(L,R,l,mid,ls[o]);
        if(mid<R) ret+=getsum(L,R,mid+1,r,rs[o]);
        return ret;
    }
    ll getmin(int L,int R,ll k){//f(x)+kx 的区间最小值
        auto p=find(-k);
        if(p.x<L) return at(L)+k*L;
        else if(p.x>R) return at(R)+k*R;
        else return p.y+1ll*p.x*k;
    }
    ll at(ll x){//f(x)
        clamp(x,-(ll)V,(ll)V);
        return begin.y+getsum(-V,x);
    }
    ll d(ll x){//f'(x)
        clamp(x,-(ll)V,(ll)V);
        return getsum(x,x);
    }
    void add(int a,int k){//+= y=k|x-a|
        begin.y+=1ll*(a+V+1)*k;
        add(-V,a,-k),add(a+1,V,k);
    }
    func(){
        // memset(this,0,sizeof(func));
        begin={-V-1,0},size=1;
        t[1]={2*V+1,0};
    }
    void print(){
        for(int i=-10;i<=10;i++) printf("%d:%lld ",i,at(i));
        puts("");
    }
}f0,f1,f2;
ll tmp;
ll solve_d(ll k){
    return f2.d((f0.find(k-1)+f1.find(k-1)).x)+k;
}
ll solve(ll k){
    auto pl=f0.find(k-1)+f1.find(k-1),
    pr=f0.find(k)+f1.find(k);
    return f2.getmin(pl.x,pr.x,k)+pl.y-pl.x*k;
}
const int N=2e5+10;
ll solve(){
    ll left=-(ll)V*N,right=(ll)V*N;
    while(left<right){
        ll mid=left+(right-left+1)/2;
        if(solve_d(mid)<0) left=mid;
        else right=mid-1;
    }
    return solve(left);
}
int h[N],w[N];
void add(int i,int v=1){
    switch((i-1)%6+1){
    case 1:
    f0.add(h[i],w[i]*v);break;
    case 2:
    f1.add(-h[i],w[i]*v);break;
    case 3:
    f2.add(-h[i],w[i]*v);break;
    case 4:
    f0.add(-h[i],w[i]*v);break;
    case 5:
    f1.add(h[i],w[i]*v);break;
    case 6:
    f2.add(h[i],w[i]*v);break;
    }
}
int main(){
    // freopen("ex_Hypochondriac8.in","r",stdin);
    // freopen(".out","w",stdout);
    int n,q,TYPE;scanf("%d%d%d",&n,&q,&TYPE);
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    for(int i=1;i<=n;i++) scanf("%d",w+i);
    for(int i=1;i<=n;i++) add(i);
    printf("%lld\n",solve());
    while(q--){
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        add(x,-1);
        if(op==1) h[x]=y;
        else w[x]=y;
        add(x);
        printf("%lld\n",solve());
    }
}