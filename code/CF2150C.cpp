#include<bits/stdc++.h>
const int N=1e5;
int v[N];
int a[N],b[N],pb[N];
bool vis[N];
int n;
using ll=long long;
typedef std::pair<ll,int> pii;
pii t[N*4];ll tag[N*4];
ll svb[N];
void pushup(int o){
    t[o]=std::min(t[o<<1],t[o<<1|1]);
}
void pushtag(int o,ll v){
    t[o].first+=v,tag[o]+=v;
}
void pushdown(int o){
    if(tag[o]){
        pushtag(o<<1,tag[o]),
        pushtag(o<<1|1,tag[o]);
        tag[o]=0;
    }
}
void build(int l=1,int r=n,int o=1){
    tag[o]=0;
    if(l==r){
        t[o]={svb[l],l};
        return;
    }
    int mid=l+r>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
    pushup(o);
}
void add(int L,int R,int v,int l=1,int r=n,int o=1){
    if(L<=l&&r<=R) return pushtag(o,v);
    int mid=l+r>>1;pushdown(o);
    if(L<=mid) add(L,R,v,l,mid,o<<1);
    if(mid<R) add(L,R,v,mid+1,r,o<<1|1);
    pushup(o);
}
void erase(int x,int l=1,int r=n,int o=1){
    if(l==r){
        t[o].first=1e9;
        t[o].second=0;
        return;
    }
    int mid=l+r>>1;pushdown(o);
    if(x<=mid) erase(x,l,mid,o<<1);
    else erase(x,mid+1,r,o<<1|1);
    pushup(o);
}
int main(){
    freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",v+i);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        for(int i=1;i<=n;i++) scanf("%d",b+i),pb[b[i]]=i;
        for(int i=1;i<=n;i++) svb[i]=svb[i-1]+v[b[i]];
        std::fill(vis+1,vis+n+1,0);
        ll ans=0;
        build();
        for(int i=1,las=1;i<=n;i++){
            int s=t[1].first,k=t[1].second;
            if(s<0){
                for(;las<=k;las++)
                    vis[b[las]]=1,
                    erase(las);
                add(las,n,-s);
            }
            if(vis[a[i]]) continue;
            add(pb[a[i]],n,-v[a[i]]);
            erase(pb[a[i]]);
            ans+=v[a[i]];
        }
        printf("%lld\n",ans);
    }
}
/*
statement:
[cYsmix - House With Legs](https://soundcloud.com/olemlanglie/cysmix-house-with-legs-original-mix)

⠀

There is a shop with $n$ objects numbered from $1$ to $n$, and only one copy of each object. According to you, the objects have values $v_1, v_2, \ldots, v_n$ (which can be negative).

Alice and Bob have their own order of preference of objects ($a_1, a_2, \ldots, a_n$ and $b_1, b_2, \ldots, b_n$ respectively). In particular, Alice's favourite object is $a_1$, followed by $a_2$, etc.; Bob's favourite object is $b_1$, followed by $b_2$, etc.

For $n$ times, one of them goes to the shop and buys her or his most favourite object still in the shop. At the end, Alice and Bob have their own sets of objects.

Now the shop is empty, and you wonder whether Alice's preferences are similar to yours. Over all sets of objects that Alice could have bought, what's the maximum sum of values according to you?

input:
1
12
-4 6 10 10 1 -8 6 2 -8 -4 0 -6
11 12 7 3 6 8 1 5 10 2 9 4
7 5 3 6 1 2 8 12 9 4 10 11
jury's output:
24
my output:
6

what is the bug?
*/