尝试使用「形式的冪級数」来解决这个问题，此题解并没有 NTT。

记 $K=\pi(M)$，即 $M$ 以内的素数个数，令其中的第 $k$ 个为 $p_k$。

问题可以简化为这样的形式：想象一个长为 $K$ 的数组，一开始所有的位置都是 $0$，然后你进行 $N$ 次操作，共有 $M$ 种操作，每次操作表现为给数组中的每个元素加上一个非负数——也就是说，如果你在原题中的整数序列末尾新加的元素为 $m=\prod_kp_k^{a_k},(1\le m\le M)$，那么 $k$ 这个位置就加上了 $a_k$。最终我们把数组中每个数字分别加一再乘起来便是我们此番操作的分数了。而我们要计算所有情况的分数之总和。

尝试使用幂级数的视角看待这个过程：对于每一个 $1$ 到 $M$ 中的正整数 $m$，把它看成一个单项式 $\prod_kx_k^{a_k}$，其中 $a_k$ 表示 $m$ 的质因子分解中 $p_k$ 的次数。不难发现，把这样的东西乘起来就可以模拟上面的操作。

于是我们可以把所有的操作放在一起成为一个多项式。记多元多项式函数 $f(x_1,x_2,\dots,x_K)=\sum_{i=1}^M\prod_{k=1}^Kx_k^{a_k(i)}$

不难想象，长度为 $n$ 的答案即为
$$
\begin{aligned}
S_n&=\sum_{i_1,\dots,i_K}\prod_{k=1}^K(i_k+1)\left[\prod_{k=1}^Kx_k^{i_k}\right]f^n\\
&=\sum_{i_1,\dots,i_K}\left[\prod_{k=1}^Kx_k^{i_k}\right]\frac{\partial^K}{\partial x_1\cdots\partial x_K}(f^n\prod_{k=1}^Kx_k)\\
&=\left.\frac{\partial^K}{\partial x_1\cdots\partial x_K}(f^n\prod_{k=1}^Kx_k)\right|_{x_1,\dots,x_k=1}
\end{aligned}
$$
其中 $\frac{\partial^K}{\partial x_1\cdots\partial x_K}$ 意为 $\frac\partial{\partial x_1}\cdots\frac\partial{\partial x_K}$ 即对每个 $x_k$ 做一次偏微分，后面那条竖线是代入的意思~~应该都知道吧~~。

这种多元函数的快速计算似乎并不在我们的能力范围内，但实际上利用题目的特殊性，我们可以使用矩阵乘法来解决它，具体方法我们稍后再谈。

完全找不到头绪。试着换元？记 $y_k=x_k-1$，由于妇孺皆知的 $\frac\partial{\partial(x+C)}=\frac\partial{\partial x}$ 其中 $C$ 为常数，有
$$
\begin{aligned}
S_n&=
\left.\frac{\partial^K}{\partial y_1\dots\partial y_K}(f^n\prod_{k=1}^K(y_k+1))\right|_{y_1,\dots,y_k=0}
\end{aligned}
$$
这里的 $f(y_1,y_2,\dots,y_K)=\sum_{i=1}^M\prod_{k=1}^K(y_k+1)^{a_k(i)}$

迎刃而解！因为所有的 $y$ 取零意味着我们只需要这坨东西的常数项，而偏微分之后能得到常数项的就是 $\left[\prod_{k=1}^Ky_k\right]$ 这一项！因此
$$
\begin{aligned}
S_n&=\left[\prod_{k=1}^Ky_k\right]f^n\prod_{k=1}^K(y_k+1)\\
&=\left[\prod_{k=1}^K(y_k+1)\right]f^n\\
\end{aligned}
$$
（请允许我的一点点符号活用，但是它真的很形象，伙计）

由于后面乘了个 $\prod_{k=1}^K(y_k+1)$，而我们又取的是 $\left[\prod_{k=1}^Ky_k\right]$ 这一项，可见 $f_n$ 中 $y_k$ 的次数要么是 $0$ 要么是 $1$。这共有 $2^K$ 种可能，$S_n$ 就是 $f^n$ 的这所有的 $2^K$ 项的和。这里的 $f$ 可视作 $\sum_{i=1}^M\prod_{k=1}^K(a_k(i)\cdot y_k+1)$，我们可以直接暴力枚举这 $2^K$ 项算出来 $f$。

由于这道题的 $K$ 出奇的小，因此 $O(8^K\log N)$ 的时间复杂度也是可接受的，也就是说，我们（甚至）可以把 $f$ 看作 $\R^{2^K}$ 空间的一个点，把多项式乘法看成线性映射，然后用快速幂加速矩阵乘法快速计算 $f^n$ 这样的东西。

题解使用了一种基于数位 DP 的方法，说实话蒟蒻我并没有看懂。