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

