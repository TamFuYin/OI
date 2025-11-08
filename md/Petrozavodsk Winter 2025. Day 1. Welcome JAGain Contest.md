# Petrozavodsk Winter 2025. Day 1. Welcome JAGain Contest

## Amusement Park

签到

## Break A Prison

还是签到

拆点跑最短路即可

## Camp

首先不合法当且仅当存在绝对众数

因此所求即为

$$
m^{2n}-\sum_{i=n+1}^{2n}\binom{2n}im\cdot(m-1)^{2n-i}
$$

尝试二项式展开，把 $m$ 都放到一起：

$$
\begin{aligned}
\sum_{i=n+1}^{2n}\binom{2n}im\cdot(m-1)^{2n-i}
&=\sum_{i=n+1}^{2n}\binom{2n}im\sum_{j\ge 0}\binom{2n-i}{j}m^j\\
&=\sum_{j\ge 0}m^{j+1}\sum_{i=n+1}^{2n}\binom{2n}i\binom{2n-i}{j}\\
&=\sum_{j\ge 0}m^{j+1}\sum_{i=n+1}^{2n}\binom{2n}j\binom{2n-j}{2n-i-j}\\
&=\sum_{j\ge 0}\binom{2n}jm^{j+1}\sum_{i=0}^{n-1}\binom{2n-j}{i-j}\\
\end{aligned}
$$

嗯，不会做

## Do The Good Assignment

与其说是「染色」，不如说是「重标号」

题意相当于要求：

- 存在一个分界点 $k$，使得
- 对于 $\le k$ 的点 $i$，$i$ 的邻域的最小值 $<i$
- 对于 $> k$ 的点 $i$，$i$ 的邻域的最大值 $>i$

考虑 DP。设 $f_{u,i,0/1}$ 表示 $u$ 的颜色为 $i$，且是否在子树处满足的方案数。

然后直接做就完了

## Experiment With Balls

神秘

## Find The Sum For Subrectangles

拆贡献，则两个点 $(x,y)$ 和 $(u,v)$ 的贡献为 $\min(x,u)\min(y,v)(H-\max(x,u)+1)(W-\max(y,v)+1)a_{x,y}a_{u,v}$

分情况讨论，拆掉 min 和 max，然后就是经典的二维数点了。

## Generate Tree From Polygon

神秘

## Hunt For Common Prefixes

考虑 Trie。

然而由于我们不能每次都走一次，所以要想想办法。

## Integers and Bracket Sequences

不难得到一个 $O(N^2)$ 的 DP

$$
f_{i,j}=
\left\{
\begin{aligned}
&\max(f_{i-1,j-1}+c_i,f_{i-1,j}) &\text{if }s_i=\mathtt{"("}\\
&\max(f_{i-1,j+1}+c_i,f_{i-1,j}) &\text{if }s_i=\mathtt{")"}\\
\end{aligned}
\right.
$$

但其实没有用。

考虑模拟费用流，发现可以，然后就做完了

