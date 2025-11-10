# 形式幂级数 24 题

有趣有趣，那么，开始吧

## お菓子

是板子啦

$$
[x^N](x+x^3+x^4+x^6)^D
$$

可以直接多项式快速幂。

也可以算 $\exp (D\ln(x+x^3+x^4+x^6))$

## 整数の組

也是板子

$$
[x^N]\frac{(1+x)(1+x+x^2)}{(1-x^2)(1-x^3)}
$$

## 数列

$$
[x^S]\left(\frac{1-x^{M+1}}{1-x}\right)^N
$$

## 数列 2

首先由于所有元素互不相同，显然我们可以求出 $B$ 的个数再乘上 $n!$。

我们考虑 $B$ 的差分数组，发现只要都填奇数就行了，所以答案就是 $[x^{\le M}]\frac{1}{1-x}(\frac{x}{1-x^2})^{N-1}$。

## 数列 3

出现了！带标号计数体系！

答案即为

$$
[x^N]\prod_{m=1}^M\sum_{i=0}^m\frac{x^i}{i!}
$$

可以直接暴力算

## 色紙

也是带标号计数体系

$$
[x^N]\left(\frac{e^x-e^{-x}}{2}\right)\left(\frac{e^x+e^{-x}}{2}\right)e^x
$$

## 硬貨

[付公主的背包](https://www.luogu.com.cn/problem/P4389)

记 $F(x)=\sum_{i=m}^{m+L-1}x^i=\frac{x^m(1-x^L)}{1-x}$，则答案为其 Euler 变换。

## jump

二元生成函数。

记

$$
F(x,y)=\frac{1+x}{1-y}-1
$$

答案为

$$
\begin{aligned}
&[x^Ny^M]\frac{1}{1-F(x,y)}\\
&=[x^Ny^M]\frac{1-y}{1-2y-x}\\
&=[x^Ny^M](1-y)\sum_{n\ge 0}(2y+x)^n\\
&=[x^Ny^M]\sum_{n\ge 0}(2y+x)^n-[x^Ny^{M-1}]\sum_{n\ge 0}(2y+x)^n\\
&=2^M\binom{N+M}{N}-2^{M-1}\binom{N+M-1}{N}\\
\end{aligned}
$$

## score

呃呃这不就直接做完了

$$
[x^K]\prod_{i=1}^N(1+A_ix)
$$

可以分治 FFT，也可以用类似付公主的背包的方法取 ln 再取 exp 做出来。

## 雙六

半在线卷积，其实就是用 CDQ 分治优化 DP。

## 順列

考虑容斥。

所以有

$$
f_n=-\sum_{0\le i<n}f _i(n-i)!\\
f_0=-1
$$

容易看出来

$$
F(x)e^x=-1\\
F(x)=-e^{-x}
$$

## 順列 2

可以看作不存在长度 $\le 2$ 的置换环。

依然可以考虑容斥。

应该是可以直接推出来的，这个跟多项式有什么关系吗？

## 連結 graph

[城市规划](https://www.luogu.com.cn/problem/P4841)

## 硬貨 2

[付公主的背包](https://www.luogu.com.cn/problem/P4389)

## 根付き木

$$
F(x)=x(1+\sum_{i\in \mathbb P}\frac{F^i(x)}{i!})
$$

注意到最小的素数为 $2$，所以考虑倍增 NTT（Newton 迭代）。

## ball

[十二重计数法](https://www.luogu.com.cn/problem/P5824)

$$
\sum_{k=0}^K\binom{N}{k}m^{N-k}\\
=\sum_{k=N-K}^N\binom{N}{k}m^k
$$

考虑斯特林公式

$$
\begin{aligned}
&\sum_{k=0}^K\binom{N}{k}\sum_{i=0}^{N-k}{N-k\brace i}\binom{m}{i}i!\\
&=\sum_{i=0}^N\binom{m}{i}i!\sum_{k=0}^K\binom{N}{k}{N-k\brace i}
\end{aligned}
$$

不会（干脆

