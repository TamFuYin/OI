# ARC202_C 总结

果然数论题还是得做一做总结才行。

下面认为 $N$ 与值域 $V$ 同阶，并不做区分。

题目中的*重复数*（repunit）$R_n$ 可以定义为 $\frac{10^n-1}9$。

**引理 0.0（重复数的 gcd）.** $\gcd(R_m,R_n)=R_{\gcd(m,n)}$。

*Proof.* $\gcd(R_m,R_n)=\gcd(R_m-R_n,R_n)=\gcd(R_{m-n}\times 10^n,R_n)=\gcd(R_{m-n},R_n)$。类似辗转相除法。

由此我们可以看出 重复数的 gcd 是简单的，考虑把 lcm 转化为 gcd 来计算。

**引理 0.1（min-max 容斥）.** $\max S=\sum_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\min T$。不证

**引理 0.2（gcd-lcm 容斥）.** $\mathrm{lcm~} S=\prod_{\varnothing\ne T\subseteq S}(\gcd T)^{(-1)^{|T|-1}}$。在每个质数的幂上考虑。

**定理 0.0（重复数的 lcm）.** 为了读者的视力着想，我们使用 $\mathrm{pow}$ 表示幂。此记 $S_d=\left\{i\mid d|A_i\right\}$
$$
\begin{aligned}
\mathrm{lcm}\{R_{A_1},R_{A_2},\dots,R_{A_N}\}
&=\prod_{\varnothing\ne T\subseteq [1,N]}R_{\gcd \{A_i|i\in T\}}^{(-1)^{|T|-1}}\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{\varnothing\ne T\subseteq [1,N]}(-1)^{|T|-1}[\gcd \{A_i|i\in T\}=d])\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{\varnothing\ne T\subseteq S_d}(-1)^{|T|-1}[\gcd \{A_i/d|i\in T\}=1])\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{\varnothing\ne T\subseteq S_d}(-1)^{|T|-1}\sum_{dk|\gcd \{A_i|i\in T\}}\mu(k)\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{\varnothing\ne T\subseteq S_d}(-1)^{|T|-1}\sum_{T\subseteq S_{dk},k\ge 1}\mu(k)\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{k\ge 1}\mu(k)\sum_{\varnothing\ne T\subseteq S_{dk}}(-1)^{|T|-1}\\
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{k\ge 1}\mu(k)[S_{dk}\ne \varnothing])\\
\end{aligned}
$$
$O(N\log N)$ 地预处理 $S$ 是否非空后，这个式子已经可以 $O(N\log N)$ 计算一个 lcm 了~~场上正是卡在这里~~，但是题目还要求前缀 lcm，考虑能不能把指数上的 $\sum$ 给消掉。

考虑对 $R$ 函数进行 Mobius 反演，但是我们的 $R_d$ 在一个底数的位置，于是不妨对其 $\log$ 进行 Mobius 反演。

令 $\log R_n=\sum_{d|n} \log F(d)$，则 $\log F(n)=\sum_{d|n}\mu(d)\log R(n/d)$，即 $R_n=\prod_{d|n}F(d)$。

可以按照定义 $O(N\sqrt N)$ 计算 $F$，这足以通过。事实上，$F$ 几乎就是 [10 次分圆多项式](https://oeis.org/A019328)。

考虑代进去会怎么样。

**定理 0.1（重复数的 lcm 之 FINAL 形式）.**
$$
\begin{aligned}
\mathrm{lcm}\{R_{A_1},R_{A_2},\dots,R_{A_N}\}
&=\prod_{d\ge 1}\mathrm{pow}(R_{d},\sum_{k\ge 1}\mu(k)[S_{dk}\ne \varnothing])\\
&=\prod_{d\ge 1}\prod_{u|d}\mathrm{pow}(F_u,\sum_{k\ge 1}\mu(k)[S_{dk}\ne \varnothing])\\
&=\prod_{u\ge 1}\mathrm{pow}(F_u,\sum_{u|d}\sum_{k\ge 1}\mu(k)[S_{dk}\ne \varnothing])\\
&=\prod_{u\ge 1}\mathrm{pow}(F_u,\sum_{d\ge 1}\sum_{k\ge 1}\mu(k)[S_{udk}\ne \varnothing])\\
&=\prod_{u\ge 1}\mathrm{pow}(F_u,\sum_{s\ge 1}[S_{us}\ne \varnothing]\sum_{k|s}\mu(k))\\
&=\prod_{u\ge 1}\mathrm{pow}(F_u,\sum_{s\ge 1}[S_{us}\ne \varnothing][s=1])\\
&=\prod_{u\ge 1}\mathrm{pow}(F_u,[S_{u}\ne \varnothing])\\
\end{aligned}
$$
形式优美至极。

考虑计算出 $S_u$ 何时不为空，即最小的 $i$ 使得 $u|A_i$，这个同样不难 $O(N\log N)$ 预处理。最后做一个前缀积就可以了。