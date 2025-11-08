# The 2023 ICPC Asia Xi'an Regional Contest

a.k.a. Osijek Competitive Programming Camp Fall 2024. Day 8. Xi'an Contest

## An Easy Geometry Problem

记 $B_i=2A_i-ik$，则 $A_{i+r}-A_{i-r}=kr+b$ 等价于 $B_{i+r}-B_{i-r}=2b$。

然后直接用线段树二分哈希维护即可。

## Counting Multisets

这种一看就是先画靶子再射箭……

首先看到可重集合排列数

$$
\binom{n}{c_0,c_2,\dots,c_n}=\binom{n}{c_0}\binom{n-c_0}{c_1}\binom{n-c_0-c_1}{c_2}\dots
$$

注意到元素取走的顺序是无碍的。

因此可以等价地看作 $\forall i,\forall i\in S,c_i\subseteq \sum_{j\in S}c_j$。

这实际上意味着 $c_i$ 两两无交。

## Counting Strings

注意到 $\gcd(l,r)=\gcd(l,l+len-1)=\gcd(l,len-1)$。

因此对于一个长度，我们只考虑与 $len-1$ 互质的位置 $l$ 即可。

SA 好像很难做，所以考虑更强的 SAM。

则我们想要求出一个区间的 $len-1$ 内，有多少个与通过线段树合并得到的 $l$ 集合（实际上是 $r$ 集合，不过是一样的）中至少一个元素互质。

考虑搜质因子，每次加入质数 $p$，对所有 $p|r$ 的位置 $r$，会使 $r$ 的祖先链上的一些点由合法变为不合法……

## Bracket Sequence

对于询问 1，考虑猫树分治。

让我们枚举中点，那么答案形如一个组合数的乘积的形式，但是很难做。

注意到 $k$ 比较小，所以其实可以对前后缀做一些东西然后 $O(k)$ 合并。

对于询问 2，设子序列的始末为 $l,r$，则还能产生 $(l-L+1)(R-r+1)$ 的贡献。

也可以差不多地处理。

## Dominating Point

我是不是做过这道题？

## An Easy Counting Problem

考虑 Lucas 定理，那么对 $a,b$ 的 $p$ 进制下每一位分别考虑，于是形如一个乘法卷积的形式，可以跑快速幂。但是过不了。不妨取一下离散对数，然后就是普通的加法卷积，可以 FFT 优化。

## An Easy Math Problem

不妨先不考虑 $p\le q$ 的限制，那么形如：$p_i+q_i\le n_i,r_i=p_i-q_i$ 的 $\{r_i\}$ 的数量。

显然诸位是独立的，直接乘起来即可。

对于 $p\le q$ 的限制，不难发现 $r$ 与 $1/r$ 的数量是一样的，所以除以 $2$ 即可。

## Elimination Series Once More

考虑一个选手 $i$ 能赢至少 $t$ 次，当且仅当 $i>>t$ 这一区间内 $i$ 是最大值。

因此二分答案之后贪心拔掉最大值把外面的最小值换进来即可。

## Max GCD

怎么全是 DS……

CN 特色

考虑枚举答案 $d$，那么我们只考虑 $d|a_i$ 的位置，然后贡献给询问。

如何判断能否贡献？只用看区间内第一个、第二个、最后一个插入的数即可。

然后不会做了

## Graph Changing

打表找规律题？

对 $k$ 分讨。

- $k=1$，一次操作之后变为完全图，此后保持不变
- $k=2$，


## Penguins in Refrigerator

题意表述不太清晰，企鹅是全部进去之后再全部出来的。

显然 $p$ 没有用，不妨记 $a=w\circ p\circ R$

考虑 $p=\argmax a$，对于 $a_i+a_p\le W$，这些 $i$ 可以任意交换，否则 $i$ 与 $p$ 的相对顺序不变。

考虑删掉这些可以任意交换的点，并乘上一个组合数的贡献，然后对 $p$ 左右两边分别搞即可。

考虑建笛卡尔树，可以二分找到第一个不能动的祖先。

对于问题 2，也是简单的。

## Prism Palace

?

## Random Variables

考虑计算 $P(M\le k)$，它等于
$$
\frac{1}{m^n}\left[\frac{x^n}{n!}\right]\left(\sum_{i=0}^k\frac{x^i}{i!}\right)^m
$$

直接多项式快速幂即可做到 $O(n^2\log n)$。

但是跑 FFT 恐怕很慢，过不了。

记 $f_{n,m}=\left[\frac{x^n}{n!}\right]\left(\sum_{i=0}^k\frac{x^i}{i!}\right)^m$，则可以递推计算。

## Python Program

签到