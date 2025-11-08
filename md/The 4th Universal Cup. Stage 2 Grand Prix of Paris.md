# Petrozavodsk Summer 2025. Day 6. Xeppelin Contest supported by Yandex

法国优良的数学传统……

## Apple Tree

好像 log 做不了，考虑根号做法。

注意到对于一个以 $u$ 为根的树，其不同深度的节点个数，的不同个数是 $O(\sqrt n)$ 的。

考虑换根 DP，用一个分块维护一下，然后貌似就做完了。

## Balatro

考虑把牌分为两类：一类 $a_i$ 特别大，一类 $b_i$ 特别大。

然后对两边分别做背包即可。

## Classement Nationale

>  Kostya has a hunch that this complicated system has the opposite effect.

我也觉得，所以不做了

## Digit Division

神秘构造题……

人 类 智 慧 大 放 光 芒

## [Euclid in Manhattan](https://scp-wiki-cn.wikidot.com/scp-4721)

考虑跑最短路，但是边数超限。

考虑 A*，用当前点到终点的欧几里得距离作为估计函数。

## Framboise 2

直接 DP 就做完了？

## [Goofy Songs](https://www.youtube.com/watch?v=wtMWCOBV0ps)

何意味

## Heure de Rush

模拟即可

## Infrared

学过初中物理的小朋友大概都知道「虚像」的作图方法。

然后就做完了。

## JamBrains

考虑每个点连向一次操作后达到的位置。那么形如基环树森林。

考虑 $u$ 次 Up 操作跨越了多少位置。

如果从 $(x,y)$ 出发，抵达 $(\max(x-u,1),\min(\min_{j=x-u}^xa_j,y))$，则跨越了 $f(x,y)=y+1+b_{x-1}-b_{\max(x-u,1)-1}-(\min(\min_{j=x-u}^xa_j,y)+1)$ 个位置，显然这个越大越好。

如果这个东西 $<r$，那么应该是比较好的。

注意到对于 $y_1<y_2,f(x,y_1)\ge f(x,y_2)$。

我们可以证明，要么整行都是好的，要么整行都是坏的。

...

## $k$ Operations

根据众所周知的算几不等式，肯定是「越不平均越好」。

所以我们直接减到较小值上即可。

如果是有序的，我们可以二分出最长可以让多长的前缀全部变成 $1$。

考虑整体二分，然后就做完了

## Lice Hopping

貌似是一个比较 Well-known 的问题。

可以证明 $d\le 3$。

对于 $d=1$，只有竹可以达到。

判断 $d$ 是否为 $2$ 可以通过简单的 树上 DP 完成。

但是题目给出了一个极为复杂的定理：

- 不存在节点有 $\ge 5$ 个非叶子邻居
- 具有 $\ge 3$ 个非叶子邻居的节点（称其为<ruby>异点<rt>Interesting<rt></ruby>）共路径（称其为<ruby>背脊<rt>backbone</rt></ruby>）
- 两两个有四个非叶子邻居的异点之间都有一个度数 $2$ 的点。

## Manhattan Graph

Manhattan 距离性质最好的一集（

显然一个嵌入是合法的当且仅当任意两点构成的矩形之间都存在至少一条路径。

其实这个限制是很严格的，因为它要求同一行或者同一列连的边一定是连起来的。

如果不考虑有环，那么只有形如「一条链上连了至多两条支链」的图是合法的，两条支链的中间部分允许翻折，两边的支链按不同方向叉出去。

考虑环，发现只有每个点双都形如一个阶梯状网格的东西，且都长在「中间部分」时才是合法的。

怎么判这个东西？

考虑每次找到一个长度为 $4$ 的简单环，然后可以确定与这一块相邻的块，然后可以确定它的相对坐标。

最后确定是否为阶梯即可。