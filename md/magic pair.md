神秘数论题~

下面我们记题目给出的 $n$ 为 $p$，而 $n$ 表示 $p-1$。

首先，应当注意到 $n\perp p$，这意味着每个数 $\bmod n$ 和 $\bmod p$ 的二元组两两不同，因此我们可以降维拆解相关性，转化为求解 $a^b\equiv c^d\pmod p$ 的四元组的个数，其中 $0\le a,c\le p,0\le b,d\le n$。~~自己做的时候第一步就转化错了~~

首先如果 $a$ 和 $c$ 其中一个是 $0$，那另一个也得是 $0$，这种情况有 $n^2$ 种。

此时 $a$ 和 $c$ 都不等于零，因此可以对它们取离散对数，转化为求解 $ab\equiv cd\pmod n$ 的个数。

同样，如果 $b$ 和 $d$ 其中一个是 $0$，那另一个也得是 $0$，这种情况有 $(n-1)^2$ 种。

不妨求解 $ab\equiv x\pmod n$ 的二元组个数 $f(x)$，那么答案即为 $\sum_{x=1}^{n-1}f^2(x)$。

可以注意到 $f(x)$ 的值只与 $\gcd(n,x)$ 有关，因为 $n\perp \frac x{\gcd(x,n)}$，所以存在它的逆元，可以两边同乘它，$ab(\frac x{\gcd(x,n)})^{-1}\equiv \gcd(x,n)\pmod n$，令 $a\gets a(\frac x{\gcd(x,n)})^{-1}\bmod n$，可以证明 $f(x)=f(\gcd(n,x))$，所以只需要对 $n$ 的所有因子求出 $f$ 即可，不用那些乱七八糟的筛法。

现在我们假设 $x|n$，由于 $ab=nk+x,\exist k\ge 0$，可以知道 $(ab)|x$。考虑枚举 $y=\gcd(a,n)$，则不难发现 $y$ 同样也整除 $x$。记 $a$ 剩下的部分 $t=\frac ay$，则显然 $t\perp\frac n y$，而且由于 $yt=a<n$，有 $t<\frac ny$，因此 $t$ 有 $\varphi(\frac ny)$ 种取值。同时我们知道了 $\frac xy$ 的部分由 $b$ 提供。不妨在等式两边和模数处同除以 $y$，则得到 $tb\equiv \frac xy\pmod {\frac ny}$，因为存在 $t$ 的逆元，因此 $b\bmod \frac ny$ 是唯一确定的，因此 $b\bmod n$ 有 $y$ 个。由此我们可以写出：
$$
f(x)=\sum_{y|x}\varphi(\frac ny)y
$$
因为状态数不多（大概小于 $2^{15}$），直接高维前缀和即可。

或者可以继续推式子
$$
\begin{aligned}
\sum_{x|n}f(x)&=\sum_{x|n}\sum_{y|x}\varphi(\frac ny)y\\
&=\sum_{y|n}d(\frac ny)\varphi(\frac ny)y\\
&=n\sum_{y|n}\frac{d(y)\varphi(y)}y
\end{aligned}
$$
可以直接算，不用高维前缀和。