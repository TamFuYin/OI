# QOJ7765: 「Xor Master」

记 $\max(x,S)=\max\{x\oplus y|y\in \operatorname{span}S\},\min S$ 同理。

1. $a_x\gets a_x\oplus v$
2. $S\gets S\cup\{x\}$
3. 询问 $\sum_{i=l}^r\max(s_i\oplus s_{l-1},S)$，这里 $s_i={\Large\oplus}_{k=1}^ia_k$

结论 $\max(a\oplus b,S)=\max(a,S)\oplus\min(b,S)$。

所以 $\max(s_i\oplus s_{l-1},S)=\max(s_i,S)\oplus\min(s_{l-1},S)$。我们需要在线段树上维护 $\max(s_i,S)$。

「区间每个数异或过之后的和」操作怎么搞？按位拆贡献处理，线段树上维护区间内每一位的 $1$ 的数量。

1 操作相当于区间异或一个 $\min(v,S)$，也可以线段树上维护。

2 操作的有效次数不超过 $\log V$ 次，可以暴力重构线段树，复杂度 $O(n\log V)$。

但是其实可以更快。因为插入一个元素要么增加一个维度要么不变。所以我们可以高斯消元得到一个行最简矩阵形式的线性基，这个形式下的线性基只需要把 $x$ 跟 $x$ 的所有零位的基向量异或起来就可以得到 $\max$，而且（如果只关注 max 的话）插入一个元素只会改变一个位置的基向量。这样单次重构就可以做到 $O(n)$ 了。

奇技淫巧：你发现线段树合并信息的过程是 $\log V$ 个值域为 $\log len$ 的数对位加，你可以把它纵向存储就可以只用 $O(\log len)$ 次二进制操作。这样可以把 $O(Q\log n\log V)$ 优化为 $O(Q\log n)$。