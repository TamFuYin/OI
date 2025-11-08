# The 3rd Universal Cup. Stage 0: Trial Contest

## A. Arrested Development

DP。设 $f_{i,j}$ 表示考虑到第 $i$ 个任务，且其中一个人使用了 $j$ 时间的情况下，另一个人使用的最少时间

## B. Champernowne Substring

[A033307](https://oeis.org/A033307)

预处理前几位，现在我们假设最多发生一次进位。

不是很会

## C. Comparator

先想想 Reflexive 怎么做。

「前 $i$ 个都不满足，第 $i$ 个满足」对于所有的 $0\le i\le n$ 构成对 $2^k$ 个 $01$ 串的划分。

你发现，这是一个 2-SAT，可以用（可撤销）并查集做。

如果当前有 $c$ 个集合，那么将提供 $2^{(c-2)/2}$ 种可能性。（因为要除去钦定为 $0$ 和 $1$ 的集合。

另外还需要判断不合法。我们对每个集合，记一下它的最小的元素及其所取的值（正/反），每次合并的时候判一下，也是可以撤销的。

那么对于 Symmetric 呢？按照上面的思路，我们需要枚举 $f(x,y)$ 和 $f(y,x)$ 终止的位置。过不了

但是你发现，实际上只有 $2^4k^2\le 1600$ 种不同的语句。对于一样的语句你没必要做两次，所以可以过。

那么 Transitive 呢？进一步拆分，实际上只有 2 种本质操作：
- $x$ 与 $y$ 不同
- $x$ 与 $y$ 相同

所以只有 $204$ 左右语句。可以三次方！

## D. Dihedral Group

这不噗叽组题吗

## E. House Deconstruction

模拟费用流，用线段树维护流量即可。

## F. Magic Bean

~~启发式搜索~~

可以构造操作交换两个元素

## G. Manhattan Walk

首先这个人是盲的，所以她一定会选择走期望时间最短的下一步，而不是像量子一样分身按概率移动。

所以我们只需要考虑当前格子的概率分布情况即可。

设 $f_{i,j}$ 为从 $(i,j)$ 走到终点的期望最短时间。$f_{r,c}=0$。

令 $f_{i,j+1}$ 和 $f_{i+1,j}$ 分别为 $a,b$，不妨令 $a<b$。

如果 $a+p\le b$，那么 $f_{i,j}=(a+(a+p/2))/2=a+p/4$。

否则，$f_{i,j}=a/2+(\int_0^{b-a}(a+x)\mathrm dx+\int_{b-a}^pb\mathrm dx)/(2p)=a/2+(a(b-a)+(b-a)^2/2+b(p-b+a))/(2p)$

## H. MountainCraft

翻转一下坐标系即可

## I. Not Another Constructive!

~~既然题目提示我们不是构造题~~，考虑 DP

需要记录前缀 `N`，`NA`，`NAC` 的个数，状态数达到了 $O(n\times n\times n^2\times k)=O(n^4k)$，完全过不了。

考虑类似 meet in the middle 的方法，在所有的 `A` 处统计贡献。

那么需要预定后缀中 `C` 的个数。状态数为 $O(n^3k)$。

其实我们不需要数数，只需要判断合法性。用 bitset 优化就能过了。

## J. Passport Stamps

二分答案

## K. Shadow Line

计算几何，懒得做

## L. Square of Triangles

[神秘](https://qoj.ac/blog/hhoppitree/blog/904)