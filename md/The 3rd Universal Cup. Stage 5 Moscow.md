## A. Counting Permutations

记 $A_i=a_i\bmod m,B_i=a_i\bmod m$。

不妨按照以 $A$ 为第一关键字升序，以 $B$ 为第二关键字降序 排序。

然后看一下它合不合法，如果合法，再看一下有多少段 $A$ 和 $B$ 都是相同的，乘下阶乘即可。

## B. Bookshelf Tracking

一次操作会把左半边 reverse，模拟即可。

## C. Painting Fences

首先你发现若干次操作最终来看是复制的一个矩形的内容。

设这个矩形是 $([xl,xr],[yl,yr])$，首先要求这个矩形是黑色的，其操作次数为
$$
\left\lceil\log_2\left(\left\lfloor\frac{r}{r-l+1}\right\rfloor+\left\lfloor\frac{n-r}{r-l+1}\right\rfloor\right)\right\rceil
$$

对 $x$ 和 $y$ 求和。

注意到 $\left\lfloor\dfrac{r}{r-l+1}\right\rfloor+\left\lfloor\dfrac{n-r}{r-l+1}\right\rfloor$ 差不多就是 $\left\lfloor\dfrac{n}{r-l+1}\right\rfloor$，而我们只需要求出它的 $\log_2$，所以只需要求出 $x$ 的长度的一段区间内的 $y$ 的最大长度。所以这是可做的。

## D. Function with Many Maximums

直接构造就好了？

## E. Building a Fence

氵

## F. Teleports

区间 DP

## G. Exponent Calculator

直接代公式
$$
e^x=\sum_{n\ge 0}\frac{x^n}{n!}
$$

肯定是不行的。

因为当 $x$ 比较小时（比如 $-20$）收敛得比较慢。

注意到 $e^x=(e^{x/256})^{256}$，所以可以先算 $e^{x/256}$，然后再给它平方 $8$ 次。

```output
$1 = $1 * 0.003906250000
$0 = 1 + $1
$2 = $1 * $1
$2 = $2 * 0.500000000000
$0 = $0 + $2
$2 = $2 * $1
$2 = $2 * 0.333333333333
$0 = $0 + $2
$2 = $2 * $1
$2 = $2 * 0.250000000000
$0 = $0 + $2
$2 = $2 * $1
$2 = $2 * 0.200000000000
$0 = $0 + $2
$2 = $2 * $1
$2 = $2 * 0.166666666667
$0 = $0 + $2
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
$0 = $0 * $0
```

## H

不会

## I

？直接让 d=i 不就行了？

## J

枚举一个 $i$，那么会产生 $\sum_{s=0}^{10^i-1}\lfloor\frac{n/10^i}{s+c}\rfloor$ 的贡献。你发现这个东西可以整除分块

但是一个好数可能产生多次贡献，所以需要容斥一下。

## K

你想一想如何合并子树信息。

令 $a_{u,L}$ 表示只考虑 $u$ 从 $u$ 开始还能向上延申 $L$ 时的收益，$f_{u,L}$ 表示能够延申 $L$ 时的子树最大收益。

则
$$
f_{u,L}=\max(a_{u,L}+\sum_{v\in son_u}f_{v,l(u,v)},\max_{v\in son_u}\{f_{v,L+l(u,v)}+\sum_{w\in son_u,w\ne v}f_{w,l(u,w)}\})
$$

记 $g_u=\sum_{v\in son_u}f_{v,l(u,v)}$，则
$$
f_{u,L}=g_u+\max(a_{u,L},\max_{v\in son_u}\{f_{v,L+l(u,v)}-f_{v,l(u,v)}\})
$$

显然一个函数的段数取决于子树内 $\sum k_i$。

所以可以用 $\sum k_i$ 做 dsu on tree？

用一个 ODT 状物维护这个离散函数即可。

## L

首先 $\min=1$ 的情况一定是最优的？

个鬼啊！君不见第三个样例的答案 $\frac 32$。

考虑前缀和，那么形如若干不等式约束：
$$
p_i-p_{i-1}\ge 0\\
\min\le p_{r_i}-p_{l_i-1}\le \max
$$

枚举 $\min$，二分 $\max$，然后跑[差分约束](https://oi-wiki.org/graph/diff-constraints/)即可？

试着跑 SPFA，果不其然 T 掉了。

注意到我们可以写成
$$
p_i/\min-p_{i-1}/\min\ge 0\\
1\le p_{r_i}/\min-p_{l_i-1}/\min\le \max/\min
$$

这两个问题是等价的！

所以我们可以在所有的 $O(m^2)$ 个分数中二分，判断是否合法。

## M

你发现其实如果树比较均匀反而不优，而如果每次加入一个点，可以让每个点至多被贡献一次。

所以答案就是 $\sum-\max$。