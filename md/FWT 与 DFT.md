引子：QOJ6211

在询问 ChatGPT™ 的过程中似乎学到了一些新的东西。

实际上这道题是经典 DP 题，根本不用那么复杂。==

*特征标*（character）是一个把 Abel 群 $G$ 的元素映射到单位圆上的函数 $\chi: G\to \mathbb C^\times$，满足对于 $x,y\in G,\chi(x+y)=\chi(x)\chi(y)$。

显然 $\chi(0)=1$，$\chi(-x)=\overline{\chi(x)}$。

如果对于所有元素 $x\in G,\chi(x)=1$，则我们称其为一个平凡特征标（trivial character），我们记作 $\chi_0$，否则是一个非平凡特征标（nontrivial character），记作 $\chi_a,a\ne 0$。

对于任意一个特征标，$\frac{1}{|G|}\sum_{x\in G}\chi_a(x)=[a=0]$，有点类似单位根反演，原理是对于非平凡特征标 $\chi(-x)+\chi(x)=0$ 抵消了。

于是我们可以定义*离散 Fourier 变换*（Discrete Fourier Transform,DFT）为

$$
\hat f(a)=\sum_{x\in G}\chi_a(x)f(x)
$$

显然我们常规的 DFT 实质就是 $(\Z_N,+)$ 上的 DFT，其中 $\chi_a(x)=\omega_N^{ax}$

Walsh-Hadamard 变换 实际上也是一种 DFT，定义在 $(\mathbb Z_2^N,\oplus )$ 上，且 $\chi_a(x)=(-1)^{|a\land x|}$。

实际上并不一定非得放到单位圆上，只要是有单位根且呈现出一种类似对数的关系的即可。比如 NTT 就是。