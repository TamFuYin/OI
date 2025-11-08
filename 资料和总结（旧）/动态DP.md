我已经彻底放弃我那半死不活的splay了。

开始研究动态DP！！！

[动态最大权独立集](https://www.luogu.com.cn/problem/P4719)！

如果去掉“动态”二字的话，这就是DP板题了。

设$f_i^0$表示选取节点i时的最大权独立集，$f_i^1$反之

有：
$$
f_i^0=\sum_{j是i的儿子}\max\{f_j^0,f_j^1\},\\
f_i^1=val_i+\sum_{j是i的儿子}f_j^0\\
$$
若定义
$$
g_i^0=\sum_{j是i的轻儿子}\max\{f_j^0,f_j^1\},\\
g_i^1=val_i+\sum_{j是i的轻儿子}f_j^0\\
$$
则
$$
f_i^0=g_i^0+\max\{f_j^0,f_j^1\}(这里j是i的重儿子)\\
f_i^1=g_i^1+f_j^0(同上)\\
$$
此时我们为了把它转化成矩乘的形式，定义运算
$$
(A*B)[i,j]=\max_{k}(A[i,k]+B[k,j])
$$
然后就得到了从$f_j$得到$f_i$的式子。（j是i的重儿子）
$$
[f_i^0,f_i^1]=[f_j^0,f_j^1]*
\begin{equation}
\left[
\begin{array}{}
g_i^0 & g_i^1\\
g_i^0 & -\infty
\end{array}
\right]
\end{equation}
$$
对吧？

又因为在我们的DFS序中，链头在前，链尾在后，所以我们实际上是“倒”着推的，柿子应该是这样的
$$
\begin{equation}
\left[
\begin{array}{}
f_i^0\\f_i^1
\end{array}
\right]
=
\left[
\begin{array}{}
g_i^0 &g_i^0\\
g_i^1 & -\infty
\end{array}
\right]
*
\left[
\begin{array}{}
f_j^0\\f_j^1
\end{array}
\right]
\end{equation}
$$
算法流程：

1. 预处理出g数组。
2. 单点修改：修改其g^1^，算出其（修改前后的）链头f，并以此更新链头的父亲的g，以此往复。
3. 最终得到的根的f即为所求
