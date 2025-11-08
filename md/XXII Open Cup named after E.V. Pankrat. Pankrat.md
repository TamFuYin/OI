# XXII Open Cup named after E.V. Pankratiev, Grand Prix of Bytedance

## A. Driverless Car II

计算几何

## B. Longest Increasing Subsequence

## C. New Equipments III

~~模拟费用流板子~~

板个鬼。增广路太多了！

注意到费用 $\le 5$。

考虑 [原始对偶算法](https://oi-wiki.org/graph/flow/min-cost/#primal-dual-%E5%8E%9F%E5%A7%8B%E5%AF%B9%E5%81%B6%E7%AE%97%E6%B3%95)。

大概就是求费用流的时候把你的 SPFA 换成 dijkstra，然后在最短路 DAG 上做分层图。

此时跑一下 dinic 最大流（OI wiki 上的那个原始对偶板子相当于 EK 算法），只要你用的边还在 DAG 上，每条流的权都是一样的，所以我们能一次得到一个区间的答案。

```c++
#include<bits/stdc++.h>
namespace flow{
    const int N=1e5+10,M=1e6;
    int nx[M],ls[N],to[M],va[M],ca[M],tot=1;
    void addhalf(int u,int v,int c,int w){
        nx[++tot]=ls[u];
        to[ls[u]=tot]=v;
        va[tot]=w;ca[tot]=c;
    }
    void add(int u,int v,int c,int w){
        addhalf(u,v,c,w);
        addhalf(v,u,0,-w);
    }
    int h[N];
    bool vis[N];
    int dis[N];
    int s,t,n;
    const int INF=1e9;
    bool dijkstra(){
        std::priority_queue<std::pair<int,int> > Q;
        std::fill(dis+1,dis+n+1,INF);
        std::fill(vis+1,vis+n+1,0);
        Q.emplace(dis[s]=0,s);
        while(!Q.empty()){
            int u=Q.top().second;Q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=ls[u],v;i;i=nx[i]){
                int w=va[i]+h[u]-h[v=to[i]];
                if(ca[i]&&dis[v]>dis[u]+w&&!vis[v])
                    dis[v]=dis[u]+w,Q.emplace(-dis[v],v);
            }
        }
        for(int i=1;i<=n;i++) h[i]+=dis[i];
        return h[s]>h[t];
    }
    int dep[N];
    bool bfs(){
        std::queue<int> Q;
        std::fill(dep+1,dep+n+1,0);
        dep[s]=1;Q.push(s);
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            for(int i=ls[u],v;i;i=nx[i]){
                if(ca[i]&&va[i]+h[u]-h[v=to[i]]==0&&!dep[v]){
                    dep[v]=dep[u]+1;
                    Q.push(v);
                }
            }
        }
        return dep[t];
    }
    int cur[N];
    int dfs(int u=s,int fl=INF){
        if(u==t) return fl;
        int ret=0;
        for(int& i=cur[u],v;i&&fl;i=nx[i])
        if(ca[i]&&va[i]+h[u]-h[v=to[i]]==0&&dep[v]==dep[u]+1){
            int f=dfs(v,std::min(ca[i],fl));
            fl-=f,ret+=f;ca[i]-=f,ca[i^1]+=f;
        }
        return ret;
    }
    int maxf,minc,ans[N];
    void solve(){
        maxf=minc=0;
        while(dijkstra()) while(bfs()){
            std::copy(ls+1,ls+n+1,cur+1);
            int f=dfs(),v=h[t]-h[s];
            // printf(">> %d %d\n",f,v);
            for(int i=maxf+1;i<=maxf+f;i++) ans[i]=ans[i-1]+v;
            maxf+=f;minc+=f*v;
        }
    }
}
using namespace flow;
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),add(u,n+v,1,-w);
    s=2*n+1,t=s+1;
    for(int i=1;i<=n;i++) add(s,i,1,0),add(n+i,t,1,0);
    flow::n=2*n+2;
    h[s]=5;std::fill(h+1,h+n+1,5);
    //初始化势能函数，使任意边 va[i]+h[u]-h[v]>=0
    solve();
    for(int i=1,cur=0;i<=n;i++){
        cur=std::max(cur,-ans[i]);
        printf("%d\n",cur);
    }
}
```

## D. Interesting String Problem

SA 板子

## E. Card Shark

如果不保证每堆牌至少有一张 high card 这道题就做不了了。

不过这道题挺简单的。

## F. Coprime Matrices

尝试调整法

```c++
#include<bits/stdc++.h>
const int N=1e6;
int p[N];
int n,m,xy;
bool checkx(int k){
    return 1<=k&&k<=m||(n-1)*m+1<=k&&k<=n*m||
    std::__gcd(p[k-m],p[k])==1||std::__gcd(p[k+m],p[k])==1;
}
bool checky(int k){
    return k%m==1||k%m==0||
    std::__gcd(p[k-1],p[k])==1||std::__gcd(p[k+1],p[k])==1;
}
bool check(int k){
    return checkx(k)&&checky(k);
}
bool inq[N];
std::queue<int> q;
void check_push(int k){
    if(!inq[k]&&!check(k)) q.push(k),inq[k]=1;
}
void check_around(int k){
    if(!(1<=k&&k<=m)) check_push(k-m);
    if(!((n-1)*m+1<=k&&k<=n*m)) check_push(k+m);
    if(k%m!=1) check_push(k-1);
    if(k%m!=0) check_push(k+1);
}
std::mt19937 rnd(time(0));
void rswap(int k){
    int l=rnd()%(n*m-2)+1;
    l+=l>=std::min(k,xy);
    l+=l>=std::max(k,xy);
    std::swap(p[k],p[l]);
    check_push(k),check_push(l);
    check_around(k),check_around(l);
}
int main(){
    int x,y,w;scanf("%d%d%d%d%d",&n,&m,&x,&y,&w);
    std::iota(p+1,p+n*m+1,1);
    std::shuffle(p+1,p+n*m+1,rnd);
    int wp;xy=(x-1)*m+y;
    for(int i=1;i<=n*m;i++) if(p[i]==w) wp=i;
    std::swap(p[wp],p[xy]);
    for(int i=1;i<=n*m;i++) check_push(i);
    while(!q.empty()){
        int k=q.front();q.pop();
        if(check(k)){
            inq[k]=0;continue;
        }
        if(k==xy){
            if(!checkx(k)) rswap(k-m);
            if(!checkx(k)) rswap(k+m);
            if(!checky(k)) rswap(k-1);
            if(!checky(k)) rswap(k+1);
        }
        else rswap(k);
        if(!check(k)) q.push(k);
        else inq[k]=0;
    }
    puts("Yes");
    for(int i=1;i<=n*m;i++){
        printf("%d",p[i]);
        if(i%m==0) puts("");
        else putchar(' ');
    }
}
```

然而过不了

其实是构造题
```
1 2 11 12 21
4 3 14 13 22
5 6 15 16 23
8 7 18 17 24
9 10 19 20 25
```

然后就做完了。

## G. Factor

这个东西叫[实际数](https://zh.wikipedia.org/wiki/%E5%AF%A6%E9%9A%9B%E6%95%B8)。

一个数 $n=\prod_{i=1}^k p_i^{\alpha_i}$ 是实际数，当且仅当 $p_1=2$，且对于 $i\ge 2$：
$$
p_i\le 1+\sigma(\prod_{j=1}^{i-1}p_j^{\alpha_j})=1+\prod_{j=1}^{i-1}\frac{1-p_j^{\alpha_j+1}}{1-p_j}
$$

对于 $<\sqrt n$ 的质数筛出来，$>\sqrt n$ 的质数搜出来。

## H. Graph Operation

把它看成一个 $01$ 矩阵而非图。

那么相当于选一个 $4\times 4$ 的子矩阵翻转。

然而，我们时刻保持它是一个对称矩阵，即每操作一个 $(i,j)$ 也要把 $(j,i)$ 也操作了。

注意到每一行每一列的 $01$ 数量不变，即度序列不变。

很难搞，但是其实可以贪心？！！

首先每次找到一条边 $(u,v)\notin G$ 且 $(u,v)\in H$。

由于度序列不变，所以必然存在 $(u,w)\in G$ 且 $(u,w)\notin H$。

同理 $v$ 也会必然存在这样一个点，记为 $x$。

然而，题目要求 $u,v,w,x$ 互不相同，但是这里 $x$ 可能等于 $w$。

所以我们这里判断一下就好了？

## I. Optimal Assortment

分数规划，式子写出来是

$$
\frac{\sum_{i=1}^n w_iv_i}{\sum_{i=0}^nw_i}\le mid\\
\sum_{i=1}^n w_i(v_i-mid)\le w_0mid
$$

那么肯定对于 $v_i-mid>0$，$w_i$ 尽量选小；对于 $v_i-mid<0$ 和 $w_0$，$w_i$ 尽量选大。

因为你要选一个子集最大化利润，也就是说可以把一个子集的 $w$ 置为 $0$，所以肯定是跟它作对，也就是说把 $v_i-mid<0$ 的项给消失了。

所以式子是
$$
\sum_{i=1}^n w_i\max(v_i-mid,0)\le w_0mid
$$

考虑把 $mid$ 视作自变量 $x$，那么左边形如 $n$ 段一次函数，其和根据 $v_i$ 进行分段，需要找到其与 $w_0x$ 相交的位置。这里所有的 $w_i$ 都是最小值，除了 $w_0$ 是最大值。

显然对 $w_i$ 和 $w_iv_i$ 做一下后缀和就能直接二分相交在哪条线段上了，时间复杂度是一个 log（在线段树上二分）

## J. Cell Tower

爆搜出所有可能决策，然后跑 DLX

## K. Xiangqi

先让马吭哧吭哧跳过去，看一下能不能单擒，然后看一下能不能马后炮。