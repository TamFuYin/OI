# The 4th Universal Cup. Stage 0: Trial Contest

悲报：由于重启电脑，把 zr20 连的总结丢失了。

可恶的咕咕噜为什么一定非要手机验证码才能登录！！

## A Totient Quotient

神秘数论。

题意：《美国数学月刊》最近刊载了一则有趣的定理：对于任意正整数 $a,b$，有且仅有一组正整数 $m,n$ 满足

- $\frac{a}{b}=\frac{\varphi(m^2)}{\varphi(n^2)}$
- $m$ 与 $n$ 在任意质数上的指数都不同
- $\gcd(m,n)$ 没有平方因子

你的任务是验证这个结论。

太神秘了改日再研究吧（咕了

怎么美国题都那么数学

## Circle of Leaf

~~我做的时候还以为是矩阵树定理~~

其实直接 DP 就完了

记 $f_{i,0/1}$ 表示 $i$ 的子树内目前有 $0/1$ 个叶子连向根，已经跟 $i$ 断开的不算。因为如果 $\ge 2$ 个就一定形成环了，所以这是对的。

## Entrapment

爆搜题

## Geometry Rush

典

## Humans vs AI

笑点解析：一开始没看到选的是*连续*子序列结果想了半天。

在 DSU on 笛卡尔树即可（启发式分裂）

## Mob Grinder

直接构造即可

## Most Scenic Cycle

神秘图论题

考虑广义串并联图方法。

- 删一度点：显然这个点绝对不可能参与到答案。
- 缩二度点：新边为两条边的权值和。
- 叠合重边：新边为两条边的 max，并用两条边的和更新答案。

但是给出的图不一定是广义串并联图，怎么办？

感性理解一下，广义串并联图一定满足题目给出的性质，而题目给出的性质又非常强。

实际上只有一种情况与广义串并联图方法不同。

- 删自环：用环长更新答案。

这种图，题目称其为<ruby>点双连通区域连通图<rt>BiConnected Regional Connected Graph</rt></ruby>，缩写为 BCRCG，是一种比广义串并联图更广泛的图。

满足其对偶图是一棵树。

RE: 草了怎么 T 掉了

## Ornaments on a Tree

DP 题。

$$
f_{u,j}=j+\max_{k_1+k_2+\dots+k_{son_i}\le K-j} \sum_{v\in son_i}f_{v,k_v}
$$

即形如一个 max-plus 卷积的形式。

用 dsu on tree 维护即可。

没那么难！

注意到由于对每个点 K 的限制是相同的，所以我们贪心地让儿子填尽量多的数就是对的。

## Polygon Partition

不做

## Popping Balloons

考虑 min-max 容斥。

考虑所有按顺序的 $(2,1),(3,1),(3,2)$ 对，我们想要求出期望意义下，这些对消失的时间的 max，一个对消失的时间为两个位置消失的时间的 min。

所以需要求出：

$$
\sum_{\varnothing \ne S\subseteq 所有非法对}(-1)^{|S|-1}\frac{n}{|\bigcup S|}
$$

好像做不了。

---

记 $X$ 表示结束时剩余序列的长度的随机变量。

则我们注意到

$$
\mathbf{Pr}[X\ge k]=\frac{\text{\# of non-decreasing subsequences of length }k}{\binom{n}{k}}
$$

那么答案 $n-\mathbb E[X]=n-\sum _{k=1}^n\mathbf{Pr}[X\ge k]$

所以我们只用求出所有「长度为 $k$ 的单调不减子序列的数量」即可。

可以用分治発発梯。

$$
f_{i,j}=\sum_{k<i,c_k\le c_i}f_{k,j-1}
$$

## SLA Tomography

一眼题

## Solar Farm

一眼题

## This Is Sparta!

注意到两个元素之间最多交换 $\log V$ 次（形如辗转相除），所以我们可以模拟快速找到下一次出现位置交换的时间。