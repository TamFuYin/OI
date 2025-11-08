# The Solution of The 3rd Universal Cup Semifinals

## A. Iridescent Universe 2

神秘几何题

## B. Queue Editor

**碰到这种「从无到有构造」的题目首先应当考虑时间倒流。**

那么，每次可以：

- 如果 $a_m$ 在 $b$ 中出现，那么可以 pop 掉 $a_m$，并在 front 处 push 进一个数，要求这个数不能在 $a$ 中出现（包括被 pop 掉的那个）
- 如果 $b_{m+1}$ 在 $a$ 中出现，那么可以 pop 掉 $b_{m+1}$，并在 front 处 push 进一个数，要求这个数不能在 $b$ 中出现（包括被 pop 掉的那个）
- 上述两种操作可以同时进行

特别地，若 $a_m\ne b_{m+1}$，上述需要两次操作。

如果我们下定决心不再维持队满，那么我们将不能 push 新的数。此时的充要条件是 $a$ 和 $b$ 完全相同。在此之前，我们要求 $a_m$ 与 $b_{m+1}$ 相同，然后我们同时 pop 这两个数，并在 $a$ push $b_1$。

也就是说，我们可以 return 当且仅当 $a_1=b_2,a_2=b_3,\dots,a_m=b_{m+1}$。

可以发现我们的目标是尽量配成尾部对齐时成对的元素。

对于已经配成对的元素比较容易处理。在 $a$ 处 push $b_1$，在 $b$ 处 push 一个没见过的元素即可。这也启示我们要保证 $b_1$ 未在 $a$ 出现。

如果两边都能弹，那么可以用类似的方法处理。

后面不会了...

## C. Adjacent Add

氵

## D. Circular Matching

在梦熊炼石模拟赛见过。~~梦熊的题不会全是从这里搬的吧。不过 UCUP 的题也是搬的~~

赛时想了一个神秘倍增，不太可做。赛后差不多独立想出来了。

首先可以发现这个相当于红球跟蓝球相配对，而且形如括号配对的形式一定是最优的。

然后你就可以把红球看作 $1$，蓝球看作 $-1$，对于一条链的答案即为前缀和的绝对值之和。在环上，相当于允许找一个地方断环为链，即找一个 $x$，求 $\sum |s_i-x|$，不难发现前缀和的中位数即为最优。

这里用到了一个**trick：把横着统计的贡献均摊到竖着统计**。赛时正是没想到这个。

然后直接用主席树维护一下就好了。

```c++
#include<bits/stdc++.h>
const int N=4e5+10;
using ll=long long;
struct data{
    int cnt;ll sum;
    data operator-(const data& b)const{
        return {cnt-b.cnt,sum-b.sum};
    }
    data operator+(const data& b)const{
        return {cnt+b.cnt,sum+b.sum};
    }
};
struct node:data{
    int ls,rs;
}t[N*10];
int n,size;
int insert(int p,int x,int l=0,int r=2*n){
    int q=++size;t[q]=t[p];
    ++t[q].cnt;t[q].sum+=x;
    if(l==r) return q;
    int mid=l+r>>1;
    if(x<=mid) t[q].ls=insert(t[p].ls,x,l,mid);
    else t[q].rs=insert(t[p].rs,x,mid+1,r);
    return q;
}
int getkth(int p,int q,int k,int l=0,int r=2*n){
    if(l==r) return l;
    int mid=l+r>>1,x=t[t[q].ls].cnt-t[t[p].ls].cnt;
    if(x>=k) return getkth(t[p].ls,t[q].ls,k,l,mid);
    else return getkth(t[p].rs,t[q].rs,k-x,mid+1,r);
}
data getsum(int p,int q,int L,int R,int l=0,int r=2*n){
    if(L<=l&&r<=R) return t[q]-t[p];
    int mid=l+r>>1;
    if(L<=mid&&mid<R) return getsum(t[p].ls,t[q].ls,L,R,l,mid)+getsum(t[p].rs,t[q].rs,L,R,mid+1,r);
    if(L<=mid) return getsum(t[p].ls,t[q].ls,L,R,l,mid);
    assert(mid<R);return getsum(t[p].rs,t[q].rs,L,R,mid+1,r);
}
char s[N];
int rt[N];
int main(){
    // freopen(".in","r",stdin);
    int q;scanf("%d%d%s",&n,&q,s+1);
    for(int i=1,pre=n;i<=n;i++){
        pre+=s[i]=='0'?-1:1;
        rt[i]=insert(rt[i-1],pre);
    }
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        int m=getkth(rt[l-1],rt[r],(r-l+1)/2);
        data L=getsum(rt[l-1],rt[r],0,m),R=getsum(rt[l-1],rt[r],m,2*n);
        printf("%lld\n",(ll)m*L.cnt-L.sum+R.sum-(ll)m*R.cnt);
    }
}
```

## E. Circular Convolution 2

感觉可以直接快速幂+闵可夫斯基和？直接做就是 $O(n\log n)$ 级别的了。

如何利用数据随机的性质：数据随机时，真正有用的数不多（感觉可以直接取前 $O(\sqrt n)$ 个甚至 $O(\log n)$ 个）

## F. Even Circuit

绷不住了，怎么看了一圈都是暴力。亏我想半天线性基

因为保证 $k\equiv 0\pmod 2$，所以可以直接 meet in the middle。

## G. Master of Cards

不会

## H. Shortcut on Tree

小清新构造题。

如果边都是无向的，那么所有点都连一下 $1$ 就好了。但是这道题是有向图。

你发现没必要每个点都连 $1$。如果 $u$ 的儿子连了 $1$，那么可以连一下 $(1,u)$ 以缩短路径长度

然后貌似就做完了。证明：考虑 $u$ 和 $v$，$u$ 可以在至少两步内走到 $1$，如果 $v$ 连的是 $(1,v)$ 那么一步就走完了；否则 $v$ 的父亲一定会从 $1$ 连，总计最多 $4$ 步。

## I. Ethanol

不难发现一定是每次移动一个无穷小量最优，这个可以打表验证。

```c++
#include<bits/stdc++.h>
const int N=1e5;
using lfloat=long double;
lfloat e[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;lfloat X;scanf("%d%Lf",&n,&X);X/=1e3L;
        for(int i=1;i<=n;i++) scanf("%Lf",e+i),e[i]/=1e3L;
        lfloat ans=0;
        int T=1e6L;
        lfloat b=X/T;
        while(T--){
            lfloat x=0;
            for(int i=1;i<=n;i++){
                e[i]=(e[i]+x)/(b+1);
                x=e[i]*b;
            }
            ans+=x;
        }
        printf("%.10Lf\n",ans);
    }
}
```

看上去很复杂，考虑只有一个瓶子的情况，每次剩下的乙醇质量，不难发现第 $k$ 次之后恰为 $\dfrac{e_1}{(1+\mathrm dx)^k}$

先证一个引理：$\lim_{\mathrm dx\to 0}(1+\mathrm dx)^{1/\mathrm dx}=\mathrm e$，取倒数即发现其为 $\mathrm e$ 的极限定义。

最终，我们发现拿走的总量为
$$
e_1-\dfrac{e_1}{(1+\mathrm dx)^{X/{\mathrm dx}}}=e_1(1-\mathrm e^{-X})
$$

考虑第二个瓶子。好难算啊不算了

## J. International Olympiad in Fishing

我们能得到的信息是什么？

1. 以 Rank 为第一关键字，编号为第二关键字的顺序。
2. 以 Suit 为第一关键字，Rank 为第二关键字，编号为第三关键字的顺序。
3. 以 Rank 为第一关键字，Suit 为第二关键字，编号为第三关键字的顺序。

试比较 $1$ 类和 $3$ 类信息。如果发生改变，那我们认为这些发生改变的数的 Rank 是相同的。

## K. Degree Sequence 3

我去，这不[<ruby>哈基米<rt>Havel-Hakimi</rt></ruby>算法](https://zh.wikipedia.org/wiki/%E5%93%88%E9%9F%A6%E5%B0%94-%E5%93%88%E5%9F%BA%E7%B1%B3%E7%AE%97%E6%B3%95)吗

大概就是，先按度数从大到小排序，然后每次 $1$ 直接贪心匹配前 $d_1$ 大（除了它自己）的点。

其实还有一个等价的 Erdős–Gallai 定理，大概就是度序列合法当且仅当 $\forall k,\sum_{i=1}^k d_i\le k(k-1)/2+\sum_{i=k+1}^n\min(d_i,k)$，当然也是降序的。

## L. Bot Friends 2

猜想：一定存在一个最优方案，使得最终把最后这个 bot 送到 $a_i$ 最小的点去。

那么，对于树上的情况，可以做一个树形 DP。若对于每个 $i$ 的祖先都有 $a_i<a_j+dis_i-dis_j$，那么我们不得不在 $i$ 处合并。进一步地观察，我们一定会在 $a_i-dis_i$ 的前缀最小值处合并。

这个结论在一般图不成立，然而仍然能给我们以启发。

例如，我们发现每个点之间的影响相当有限。我们可以把每个点分开处理，对每个点 $i$，找到使 $dis_{i,j}+a_j$ 最小的 $j$ 并在 $j$ 处合并。不难发现如果 $i\ne j$，那么 $j$ 找到的这个点一定是 $j$ 自己。因此关系形如若干菊花。如果展开来看，每个菊花在原图上形如一个连通子图。

如何把这些菊花合并起来呢？注意到这些菊花中心的 $a$ 都是比较小的，阻碍它们相连的是路程。所以实际上我们可以一碰到别人就合并，把这些子图缩成一个点，相当于找一棵生成树，钦定某一点为根，那么合并的费用是所有的边长加上每个点的 $a$ 乘上儿子个数，即每个点的 $a$ 乘上邻域大小减一，再加上根节点的 $a$。可以用最小生成树解决。

```c++
#include<bits/stdc++.h>
const int N=5e5+10,M=2e6+10;
using ll=long long;
ll a[N];
int nx[M],ls[N],to[M],va[M],tot;
int n;
void clear(){
    std::fill(ls+1,ls+n+1,0);
    tot=0;
}
void add(int u,int v,int w){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
    va[tot]=w;
}
std::priority_queue<std::pair<ll,int> > Q;
ll dis[N];
int fr[N];
bool vis[N];
void dij(){
    for(int i=1;i<=n;i++) dis[i]=a[i],fr[i]=i,vis[i]=0,Q.emplace(-dis[i],i);
    while(!Q.empty()){
        int u=Q.top().second;Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=ls[u];i;i=nx[i]){
            if(dis[to[i]]>dis[u]+va[i]){
                fr[to[i]]=fr[u];
                dis[to[i]]=dis[u]+va[i];
                Q.emplace(-dis[to[i]],to[i]);
            }
        }
    }
}
struct edge{
    int u,v;ll w;
    bool operator<(const edge& b)const{
        return w<b.w;
    }
}e[M];
int pa[N],sz[N];
int findp(int x){
    if(pa[x]==x) return x;
    return pa[x]=findp(pa[x]);
}
void merge(int x,int y){
    x=findp(x),y=findp(y);
    if(sz[x]<sz[y]) std::swap(x,y);
    sz[x]+=sz[y];pa[y]=x;
}
int main(){
    // freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%lld",a+i);
        clear();
        for(int i=1,u,v,w;i<=m;i++)
            scanf("%d%d%d",&u,&v,&w),
            add(u,v,w),add(v,u,w);
        dij();m=0;
        for(int u=1;u<=n;u++)
            for(int i=ls[u],v;i;i=nx[i])
                if(fr[u]!=fr[v=to[i]])
                    e[++m]={fr[u],fr[v],va[i]+dis[u]+dis[v]};
        std::sort(e+1,e+m+1);
        std::iota(pa+1,pa+n+1,1);
        std::fill(sz+1,sz+n+1,1);
        ll ans=0;
        ll min=LLONG_MAX;
        for(int i=1;i<=n;i++)
            if(fr[i]!=i) ans+=dis[i];
            else ans-=a[i],min=std::min(min,a[i]);
        ans+=min;
        for(int i=1;i<=m;i++)
            if(findp(e[i].u)!=findp(e[i].v))
                merge(e[i].u,e[i].v),ans+=e[i].w;
        printf("%lld\n",ans);
    }
}
```

## M. Traveling in Cells 3

首先如果每个点 $\equiv 0\pmod a$，那么答案就是通通飞到中位数。

考虑拓展这个思路，找到 $\lfloor x_i/a\rfloor$ 的中位数，那么答案一定在这个长度为 $2a$ 的块中，每个人最多飞一次。每次飞的人一定是一个前缀或者后缀，枚举这个分界点就能快速算了，需要二分找到中位数。

细节略多，不想调了~~还是说我的思路其实是错的？~~
