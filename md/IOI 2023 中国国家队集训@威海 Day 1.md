# IOI 2023 中国国家队集训@威海 Day 1

## A. Flip it and Stick it

### $|T|=1$

特判

### $|T|=2$ 且 $T_1\ne T_2$

考虑跟踪白色段的个数和黑色段的个数。

每次操作会减少一个白色段的个数或者黑色段的个数，或者都减少。

直接贪心搞就可以了。

### $|T|=2$ 且 $T_1= T_2$

我们在两个连续的白色格子之间画一条白线，在两个连续的黑色格子之间画一条黑线，那么只有当一次操作在黑线和白线之间交换才是合法的

### $|T|=3$

## B. Travelling Trader

怎么又是这种讨论的

### $K=1$

DFS

### $K=2$

## C. Triangle Collection

我们把 $a_i=c_i\bmod 2$ 看作落单的需匹配的，$b_i=\lfloor c_i/2\rfloor$ 看作允许匹配的个数。

那么形如二分图匹配，根据 Hall 定理，存在对 $a$ 而言的完美匹配当且仅当
$$
\forall S\subseteq [1,n],\sum_{i\in S}a_i\le \sum_{i=1}^n[\min S\le 2i-1]b_i
$$

由于只有 $\min S$ 重要，所以不妨转化为
$$
\forall i\in[1,n],sa_i\le sb_{\lceil (i+1)/2\rceil}
$$

其中 $sa$ 表示 $a$ 的<ruby>后缀和<rt>suffix sum</rt></ruby>，$sb$ 同理。

如果我们允许不匹配，那么相当于减少一个 $a$，不难发现即为求
$$
\max(0,\max_{i=1}^n\{sa_i-sb_{\lceil (i+1)/2\rceil}\})
$$

然后直接用线段树维护即可。