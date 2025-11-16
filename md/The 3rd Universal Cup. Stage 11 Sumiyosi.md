# [NPCAPC 2024](https://atcoder.jp/contests/npcapc_2024)

## Welcome to NPCAPC

你发现这个 DP 形如自动机路径计数，总共只有 $7\times 7=49$ 个状态，预处理矩阵快速幂即可。

## Some Sum of Subset

不妨对其排序。那么每个合法的子序列的贡献即为一个组合数，枚举分界点，DP 即可

## Solve with Friends

假设最终选了 $S$ 的问题给了なむか君，那么答案即为 $\sum_{i\in S} A_i+\Sigma C_{|S|}+\sum_{i\notin S}B_i+\Sigma D_{n-|S|}$。

因此给 $A_i-B_i$ 排序之后，直接枚举 $|S|$ 即可。

## Two Box

~~考虑予定调和 DP，设 $f_{i,j}$ 表示~~

不是 $M$ 怎么才 $\le 15$，那不直接秒了

## Aim High

可以看作任意行走但只能「吃子」的（国际象棋中的）兵。

$N$ 小得可怜，实际上操作次数大概应该就是 $2^N$ 或者 $N!$ 级别的，应该直接构造即可。

## Train Seats

不妨对 $A$ 排序，考虑一个 $B_i=A_{i+1}-A_i$ 的贡献。

考虑设 $T_i$ 表示 $i$ 有人坐下的时间。

不难发现即为 $T[1,i]$ 的后缀最小值个数加上 $T[i+1,n]$ 的前缀最小值个数减一。

根据广为人知结论，一个随机排列的前缀最小值个数的期望值是调和级数 $H_n$。

因此这里的期望值即为 $H_{i}+H_{n-i}-1$。

……等等我看错题了，这题是最优化。

则问题是：进行 $N-1$ 次操作，第 $i$ 次操作将挑选一个 $B$，然后删掉他，并贡献 $B\times (N-i)$。

考虑每次一定是挑一个最小值或者最大值，我们可以三分出这个分界线。

## Many Common Segment Problems

考虑 Common Segment 怎么做。

考虑交集非空，其实就是 $\max L\le \min R$，我们不妨枚举 $k=\max L$，然后再 $L\le k$ 且 $R\ge k$ 的元素中任意选即可，要保证至少有一个 $L=k$ 被选，容斥减去 $L<k$ 且 $R\ge k$ 的子问题即可。

两个问题是差不多的，下面只考虑计算 $L\le k$ 且 $R\ge k$ 的计数。

注意两个元素之间是独立的，所以直接就做完了。

## Music Game

由于乘法和加法都满足交换律，所以可以 **exchange argument**

不妨记 $p_i=A_i/B_i$

假设按 $i$ 前已花费了 $x$ 时间，则按完 $i$ 之后时间变为 $x'=p_i(x+T_i)+(1-p_i)(x+T_i+x')$，解得 $x'=\dfrac{x+T_i}{p_i}$。

如果先按 $i$ 再按 $j$，则时间为 $((x+T_i)/p_i+T_j)/p_j=(x+T_i+T_jp_i)/(p_ip_j)$，否则为 $(x+T_j+T_ip_j)/(p_ip_j)$，因此比较 $T_i+T_jp_i<T_j+T_ip_j$，当且仅当 $T_i/(1-p_i)<T_j/(1-p_j)$，因此是一个全序。

## Left Equals Right

显然至多只有一个 $i$ 是合法的，因此不用容斥。

Meet In The Middle DP 即可。

## Again Permutation Problem

即求给定置换通过复合张成的子半群的所有逆序对之和。

前置知识：[Schreier–Sims algorithm](https://codeforces.com/blog/entry/111290)。

## Peace with Magic

我们先不考虑 $D_i$ 的限制，考虑把 $H_1,H_2,\dots,H_N$ 变高为 $X_1,X_2,\dots,X_N$ 的最小操作次数。

区间加问题可以考虑差分数组，记 $H'_i=H_{i+1}-H_i,X'_i=X_{i+1}-X_i$，则一次操作相当于选择 $l,r$ 满足 $H'_i=0,\forall i\in[l,r)$，然后 $H_{l-1}+1$，$H_r-1$。

然后这里的 $D_i$ 就相当于要求 $|X'_i|\le D_i$。

现在我们的 DP 状态终于能与 $D$ 有关了，后面直接做 DP 即可。

## Construction of Town

注意到如果 $M=N-1$，则答案一定为菊花图。

大胆猜想：对于 $M>N-1$ 的情况，一定是在菊花图上加边，且怎么加都行，因为答案的上界就是 $MX_1+(N(N-1)-M)X_2$。

## Admired Person

考虑对 $A$ 和 $B$ 都排序一下，然后做一下 $O(n^2)$ DP 即可。

## Product Matrix

考虑插值，分别带入 $1,2,\dots,2^M$，则我们相当于每次给维护的矩阵乘上 $\dfrac{P(2^{i+M})}{P(2^{i})}$，但是矩阵不一定有逆……

其实定长区间信息维护有很简单的方法，最简单的一种是每 $M-1$ 分一块，然后每块内维护前缀信息和后缀信息，每次合并一下即可。

## New School Term

经典题啊，我绝对做过

贪心从大到小考虑，用 2-SAT 维护。