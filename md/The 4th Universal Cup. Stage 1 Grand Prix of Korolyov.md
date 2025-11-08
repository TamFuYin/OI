# GP of Korolyov

## Grid Problem

注意到

$$
\begin{matrix}
    2&1\\
    1&2
\end{matrix}
$$

和

$$
\begin{matrix}
    2&5&2\\
    5&5&5\\
    2&5&2
\end{matrix}
$$

每行每列的和都整除于 $3$。

打一下表可以猜想合法当且仅当每行每列的和都整除于 $3$。

其实可以用题目的两个矩阵组合出一个 $1\times 1$ 的值为 $3$ 的矩阵，所以是对的。

---

考虑多项式

$$
F(r_1,r_2,\dots,r_h,c_1,c_2,\dots,c_w)=\prod_{i=1}^h\prod_{j=1}^w\sum_{t=0}^k(r_ic_j)^t
$$

则，答案为
$$
\sum_{3|s_i,3|q_j}[r_1^{s_1}r_2^{s_2}\cdots r_h^{s_h}c_1^{q_1}c_2^{q_2}\cdots c_{w}^{q_w}]F(r_1,r_2,\dots,r_h,c_1,c_2,\dots,c_w)
$$

看到自变量的指数上的整除问题，考虑单位根反演：

$$
[n|k]=\frac{1}{n}\sum_{i=0}^{n-1}\omega_{n}^{ik}
$$

那么答案为

$$
\begin{aligned}
&3^{-q-w}\sum_{0\le s_i<3}\sum_{0\le q_j<3}F(\omega_3^{s_1},\omega_3^{s_2},\dots,\omega_3^{s_h},\omega_3^{q_1},\omega_3^{q_2},\dots,\omega_3^{q_w})\\
&=3^{-q-w}\sum_{0\le s_i<3}\sum_{0\le q_j<3}\prod_{i=1}^h\prod_{j=1}^w\sum_{t=0}^k\omega_3^{(s_i+q_j)t}
\end{aligned}
$$

不难发现 $s_i,q_j$ 之间的顺序没有影响，所以我们只需要看每种有多少个即可。

可以对 $(s_i+q_j)\bmod 3$ 和 $k\bmod 3$ 进行分讨，不难 $O(n^2)$ 求出答案。

## Domain Compression

注意到一条边存在，当且仅当中间所有的点都被删除。

假设一条路径的长度为 $d$，那么他可以对所有 $k\ge d-1$ 贡献 $\binom{n-d-1}{k-(d-1)}$ 的系数。

所以形如一个卷积的形式，然后就做完了

## Staple Stable

相当于求
$$
\operatorname{minimize} a+b-2\\
s.t.~\left\lceil\frac{h}{a}\right\rceil\times\left\lceil\frac{w}{b}\right\rceil\le s
$$

整除分块即可

## Sequence Is Not Subsequence

构造题

考虑增量构造。

## Coffee Shops

怎么又是构造。

考虑任意一个 $2\times 2$ 的方格，其最大值必然不可能出现在答案中。

所以存在上界：$\lfloor 3n/2\rfloor$。

对于奇数 $n$，这个上界是可以达到的，只要让最大值出现在 $a_1,a_3,a_5,\dots,a_n$ 即可。

然而对于偶数 $n$，这个上界无法达到，然而 $3n/2-1$ 是可以达到的，只要让最大值出现在 $a_1,a_3,a_5\dots,a_{n-1},b_1$ 即可。

## Yet Another MST Problem

mex 是困难的，考虑转化为未出现元素的 min。

记 $a_i=[0,n)\backslash [l_i,r_i]$。

那么 $(i,j)$ 的边权即为 $\min a_i\cap a_j$。

记前缀 min 为 $pf_i$，后缀 min 为 $sf_i$。

则边权为 $\min(pf_{\min(l_i,l_j)-1},sf_{\max(r_i,r_j)+1})$。

若干次分讨之后，边权只与 $i$ 相关，所以可以线段树辅助建边。

对边权排序之后，线段树维护区间内是否纯色，然后可以对每种颜色进去连边。

## Cyclic Topsort

如果不考虑 $a_1$，我们可以每次贪心删掉入度为 $0$ 的点。

困难

## Misread Problem

考虑一个 $b_i=x$ 的代价，发现等于 $\sum_{j=1}^k |a_{j,i}-x|$。

不难发现一定可以得到一个凸函数。

然后答案就是若干个这样的凸函数的 min-plus 卷积，用 slope trick 维护即可。

## troS XEM

根据神秘结论，当 $n\ge 17$ 时，我们只需考虑 $a_i\in \{0,1,2,3\}$，然后可以 DP

## Yet Another Constructive Problem

~~似曾相识~~

注意到，如果你有两个长度为 $m$ 的子序列 $a,b$，那么必然存在长度为 $m$ 的子序列 $c$，使 $\operatorname{LIS}(c)\in [\operatorname{LIS}(a),\operatorname{LIS}(b)]$。

这是因为当其移动时，LIS 要么增加 $1$，要么减少 $1$，要么不变。

类似拟阵（也许

所以我们希望找到长度为 $m$ 的子序列 的 LIS 的最小值和最大值。

最大值是简单的，直接截取整个排列的 LIS 的一部分即可。

考虑 RSK 插入，则 LIS 等于杨表第一行长度。

考虑从底向上选，直到总长 $\ge m$，然后得到的就是最小的 LIS。

## Robot Construction

注意到我们**不关心**每个初始高度对应什么最终高度，只关心**可能有什么最终高度**。

注意到最终高度一定形如一段前缀，不妨记为 $[0,k]$，那么通过一个 $h_i$ 之后会变为 $k\gets \max(k-h_i,h_i-1)$。

然后就很简单了。
