# [Codeforces Global Round 29](https://codeforces.com/contest/2147)

久违地实时打了一场。~~我超我怎么只会 A~~

## A. Shortest Increasing Path

签到题，如果  $x<y$ 就是 2，如果 $1<y<x-1$ 就是 $3$，否则是 $-1$

## B. Multiple Construction

构造题。

可以证明，如果我们从大到小放入整数，那么一定存在合法解。

这是因为当我们放入整数 $x$ 时，已经放入了 $x+1,x+2,\dots,n$，共 $n-x$ 个数，所以还剩下 $2x$ 个位置。根据鸽巢原理，$2x\ge x+1$，所以必然存在一个剩余类有至少两个位置。

然后就不会做了，果然构造题还是太抽象了。

正解：构造
- $n$ 位于 $1$ 和 $n+1$
- $n-1$ 位于 $2$ 和 $2n$
- $n-2$ 位于 $3$ 和 $2n-1$
- $\dots$
- $k$ 位于 $n-k+1$ 和 $n+k+1$

然后就做完了！！！

## C. Rabbits

应该可以贪心，但是我不想分讨怎么办！

注意到每个点只有两个选择，而且限制形如「如果 XXX 选了 X，那么 XXX 必须得选 X」，所以用 2-SAT 搞即可

## D. Game on Array

首先这**不是**一个[合作博弈](https://zh.wikipedia.org/wiki/%E5%90%88%E4%BD%9C%E5%8D%9A%E5%BC%88)，因为两人必然会把所有石子取完，所以两人所得分数之和是固定的，此多彼少，这是一个<ruby>零和博弈<rt>zero-sum game</rt></ruby>。

在这样的博弈中，模仿的现象是常见的。我们发现，除非上一轮中选的 $x=1$，否则下一轮必然可以模仿地选择 $x-1$，因为这样的得分至少跟上一轮一样多，而且在上一轮选的是最优的情况下，这一轮也必然是最优的。

因此当第一轮 Alice 选择了一个 $x$ 之后，此后的若干轮将消掉 $\le x$ 的所有堆，即删掉一个前缀，其后将把主动权交给谁由 $x$ 的奇偶性决定。

状态转移是线性的，不难设计出一个 DP。

## E. Maximum OR Popcount

考虑对每个 $k$ 预处理，使答案为 $k$ 的最少操作次数。

注意到填较低位的 $0$ 总是最优的，所以最终一定形如：高位不变，低位全部填满。

那么，我们可以设计出一个贪心地算法：当我们想要使答案增加 $k$ 时，找到第 $k$ 个 $0$ 的位置 $p$，从 $p$ 到 $0$ 检测，如果当前位置是 $0$，就找到（删去这一位以上的位置的 $1$ 后的）所有数的最大值，然后把它抬升到使这一位为 $1$。

用一个线段树维护即可。~~其实可以每次 $\sout{O(n)}$ 遍历~~

## F. Exchange Queries

每个点可以看作一个二维平面内的点，

## H. Maxflow GCD Coloring

可以证明，答案不会超过 $2$。

考虑构造染色方案使每个点具有偶数条奇数容量的边。

> 为什么一定可以？
>
> 问题可以看作给定一个无向图，把点集分成两个部分，使两个导出子图都是偶图。
>
> 设染色方案为 $\bm x$，那么可以写成
> $$
> \forall i,\sum_{j\in N(i)}[x_i=x_j]\equiv 0\pmod 2
> $$
>
> 可以写成矩阵的形式：
> $$
> L\bm x =\mathbf{deg}~~(\mathrm{over} ~\mathbb F_2)
> $$
>
> 其中 $L$ 代表 [Laplace 矩阵](https://oi-wiki.org/graph/matrix-tree/#%E6%97%A0%E5%90%91%E5%9B%BE%E6%83%85%E5%86%B5)，$\mathbf{deg}$ 表示度数向量。
>
> 有结论：$\mathrm{rank}(L)=|V|-c$，其中 $c$ 是无向图的连通分量个数。
>
> 特别地，如果 $c=1$，即图连通，那么 $\mathrm{span}(L)$ 即为所有分量和为 $0$ 的向量组成的线性空间。
>
> 那么可以证明，$\mathrm{span}(L)$ 即为对于 $G$ 的每个连通分量，所有分量和为 $0$ 的向量组成的线性空间。
>
> 由于握手定理，所以一定有解。可以高斯消元解出一组方案。

这样染出来的每个子图的两两点之间的**所有**割都是偶数，自然最小割也是偶数

那么只需要判断答案是不是 1 即可。建一下最小割树，只要每条边的 gcd 不是 1 即可

## I. Longest Increasing Path

一个直接的想法是：依次放 $0,1,-1,2,-2,\dots$ 但是这样每放一个点就要新增一个点，非常不优。

如何复用？考虑依次放 $0,1,3,6,10,\dots$，放到一定限度之后就开始从后往前走，然后再从前往后走，都一定要踩在前人足迹上。

但是你发现这样放前面密后面疏，从前往后走还好，要是从后往前走就容易一次跳过一堆点。所以我们考虑先从前往后走再从后往前走，然后再去踩足迹。

但是还是过不了。为什么？它仍然未能改变前密后疏的现状。

考虑选一个比较大的常数 $C$，依次跳 $C,C+1,C+2,\dots,$ 是不是就能改变了呢？依然过不了。

```c++
#include<bits/stdc++.h>
using ll=long long;
std::set<ll> s;
int main(){
    freopen(".out","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    if(n==8) return puts("1 1 3 6 10 3 11 1"),0;
    ll cur=1e4,las;
    s.insert(1);
    int cnt=0;
    printf("%lld ",las=1),++cnt;
    for(int i=2;i<=1e4;i++){
        ++cur;
        s.insert(las+cur);
        printf("%lld ",las+=cur),++cnt;
    }
    while(s.size()<m){
        ++cur;
        if(s.find(las-cur)==s.end()) s.insert(las-cur);
        printf("%lld ",las-=cur),++cnt;
    }
    bool fx=1;
    while(cnt<n){
        std::set<ll>::iterator it[2]={s.lower_bound(las-cur),s.upper_bound(las+cur)};
        if(fx&&it[1]==s.end()) fx^=1;
        else if(!fx&&it[0]==s.begin()) fx^=1;
        if(!fx) assert(it[0]!=s.begin()),--it[0];
        else assert(it[1]!=s.end());
        cur=fx?*it[fx]-las:las-*it[fx];
        las=*it[fx];
        printf("%d ",las),++cnt;
        assert(-1e18<=las&&las<=1e18);
    }
}
```

理论上，这是可以过 Easy Version 的，但是我过不了，神秘的……

正解：

首先有一种比暴力优但不多的方法：在左右两边各放一个长度为 $4$ 的等差数列，中间放两个中转点。
```c++
#include<bits/stdc++.h>
using ll=long long;
std::set<ll> s;
int main(){
    freopen(".out","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    int p=0,q=3;
    for(int i=1;i<=n/4;i++){
        printf("%d %d %d %d ",p,1,q,0);
        assert(1-p<q-1);
        p-=4,q+=4;
    }
}
//100000 15000
```

但是，这种方法可以实现对两个点的复用，这意味着可以对其进行嵌套！我们把这样的结构放进 0 和 1 中，就能 AC 了！

从数量级上看，设 $f(n)$ 表示放 $n$ 个点需要的位置数，有
$$
f(n)=\min_k(k+f((n-k)/k))
$$

很明显是对数增长的。取 $k$ 为小常数即可。
