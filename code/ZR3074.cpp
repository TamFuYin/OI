/*
首先这个 k 即为区间图的色数。由于区间图是弦图，所以色数等于最大团大小。

因此如果给定选择了哪些区间，则 k 即为每个点被覆盖的区间数的最大值。

我们考虑证明一个事实：存在一种策略，使得每个区间只在 k\ge f_i 时被选。

考虑按照 r_i 从小到大排序，然后对于每种颜色维护一个当前选择了的右端点的最大值 b_j，每次贪心地插到能插的最右的区间。不难发现这是最优的。

此时，可以发现当 k 增大时，任意时刻 b_j 序列仅仅在末尾增加一个元素。因此每个区间仅在 k\ge f_i 时被选。

然后可以考虑整体二分把所有的 f 都求出来，按 r_i 从小到大排序，用线段树维护即可。

作者：tanfuxuan
*/

#include<bits/stdc++.h>
const int N=1e5+5;
struct interval{
    int l,r;
    bool operator<(const interval& other)const{
        return r<other.r;
    }
}a[N];
int n,m;
namespace seg{//区间加，区间求 max
    int t[N*4],tag[N*4];
    void pushup(int p){
        t[p]=std::max(t[p<<1],t[p<<1|1]);
    }
    void pushdown(int p){
        if(tag[p]){
            t[p<<1]+=tag[p];
            t[p<<1|1]+=tag[p];
            tag[p<<1]+=tag[p];
            tag[p<<1|1]+=tag[p];
            tag[p]=0;
        }
    }
    void update(int L,int R,int v,int l=1,int r=m,int o=1){
        if(L<=l&&r<=R){
            t[o]+=v;
            tag[o]+=v;
            return;
        }
        pushdown(o);
        int mid=l+r>>1;
        if(L<=mid) update(L,R,v,l,mid,o<<1);
        if(R>mid) update(L,R,v,mid+1,r,o<<1|1);
        pushup(o);
    }
    int query(int L,int R,int l=1,int r=m,int o=1){
        if(L<=l&&r<=R) return t[o];
        pushdown(o);
        int mid=l+r>>1,ans=0;
        if(L<=mid) ans=std::max(ans,query(L,R,l,mid,o<<1));
        if(R>mid) ans=std::max(ans,query(L,R,mid+1,r,o<<1|1));
        return ans;
    }
}
std::vector<interval> left,right;
int s[N];
void solve(int l,int r,int L,int R){
    if(l>r) return;
    if(L==R){
        s[L]+=r-l+1;
        return;
    }
    int mid=L+R>>1;
    left.clear(),right.clear();
    for(int i=l;i<=r;i++){
        if(seg::query(a[i].l,a[i].r)<mid)
            seg::update(a[i].l,a[i].r,1),
            left.push_back(a[i]);
        else
            right.push_back(a[i]);
    }
    int ls=left.size();
    std::copy(left.begin(),left.end(),a+l);
    std::copy(right.begin(),right.end(),a+l+ls);
    solve(l+ls,r,mid+1,R);
    for(int i=0;i<ls;i++)
        seg::update(a[l+i].l,a[l+i].r,-1);
    solve(l,l+ls-1,L,mid);
}
int main(){
    // freopen("ex_a2.in","r",stdin);
    // freopen("my_ex_a2.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].l,&a[i].r);
    std::sort(a+1,a+n+1);
    solve(1,n,1,n);
    for(int i=1;i<=n;i++) s[i]+=s[i-1];
    for(int i=1;i<=n;i++) printf("%d\n",s[i]);
}