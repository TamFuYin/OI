# CCPC 2024 Chongqing Site

## A. 乘积，欧拉函数，求和

注意到 $\mathrm{id}=\varphi*1$，所以 $\varphi=\mu*\mathrm{id}$

$$
\begin{aligned}
&\sum_{S\subseteq [1,n]}\varphi\left(\prod_{i\in S} a_i\right)\\
&=\sum_{S\subseteq [1,n]}\sum_{d_i|a_i,\forall i\in S}\mu\left(\prod_{i\in S} d_i\right)\left(\prod_{i\in S} \frac{a_i}{d_i}\right)\\
&=\sum_{d_i|a_i}\mu\left(\prod_{i} d_i\right)\left(\prod_{i} \left([d_i=1]+\frac{a_i}{d_i}\right)\right)\\
\end{aligned}
$$

显然非零的 $\mu\left(\prod_{i} d_i\right)$ 并不多，这是因为 $\mu$ 要求每个质因子最多出现 $1$ 次。

注意到 $\pi(\sqrt{3\times 10^3})=16$，可以做不交并卷积！

大概就是普通的 FWT，但是你记一下 popcount，要求 $|a|+|b|=|c|$，其中 $c=a\oplus b$，这样就是不交并了！

对于剩下的大质因子，我们可以用它划分等价类，枚举是否选择这个质因子，以及选择哪个 $i$。

我们不妨记 $c_s$ 表示前 16 个质数的二进制表示的实际的值。记 $mp_i$ 表示 $i$ 中唯一一个不是前 16 个质数的质数。

记 $F_i(x)=\sum_{c_s|(a_i/mp_i)}([s=\varnothing]+a_i/c_s)x^s$

那么相当于每次卷一个 $\prod_{mp_i=k}F_i(x)+\sum_{mp_i=k}\frac{F_i(x)-1}{k}\prod_{mp_j=k,i\ne j}F_j(x)$。

维护一下前缀积后缀积就可以了。

但实际上有值的位不会超过 $6$ 个，所以暴力卷应该也可以？

$F_i(x)=1+a_i\sum_{c_s|(a_i/mp_i)}x^s/c_s$

如果只看后面的 $\sum_{c_s|(a_i/mp_i)}x^s/c_s$ 部分的话，可以发现后面无论合出什么，其系数都是固定的，所以可以用 bitset 优化？