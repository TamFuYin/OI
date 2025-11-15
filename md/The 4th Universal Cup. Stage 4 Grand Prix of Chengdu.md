# GP of Chengdu

## A lot of Paintings

如果我们发现 $\sum a_i=100$，那么可以直接令 $b_i=a_i$。

否则，我们考虑令 $b_i=a_i\times 10+x_i$，然后使 $\sum b_i=1000$。依次类推，这是简单的。

## Blood Memories

状压 DP + 矩阵快速幂

## Crossing River

是经典问题呐，DP 做完了

这道题小时候抱过我.jpg

## Deductive Snooker Scoring

题面长，不想看

## Escaping from Trap

不是很懂，二元二次方程不是随便问几次就能问出来了吗？

## Following Arrows

构造题。

首先由于这个步数很大，而网格很小，我们需要构造一个网格使步数以指数级增长，这里给出一个例子

```
RRRRRRRD
DDLLLLLL
DRRRRRRD
DDLLLLLL
DRRRRRRD
DDLLLLLL
DRRRRRRD
DDLLLLLL
```

然后你发现这个框架下每个格子翻转之后产生的贡献是一定且独立的。可以用类似背包的方式计算出答案。

## GCD of Subsets

显然改成 $k$ 一定是最优的。

如果 $k\nmid a_i$，那么 $a_i$ 永远不能被选，我们可以优先改这些数。

所以问题转化为，给你 $n$ 个二进制数，求最大划分，使每组内的或等于全集

不会

## Heuristic Knapsack

显然我们只要让重量和价值呈反比两人选的就一样了。

## Inside Triangle

不做

## Judging Papers

这不是普及题吗

## K-Coverage

先预处理每个位置覆盖的线段的数量。

然后我们只关心每个点是否被覆盖了 $k$ 或者 $k+1$ 或者 $k-1$ 次，用一个树状数组维护这个的区间和。

然后我们找到覆盖 $k-1$ 次 减 覆盖 $k$ 次的最大区间，然后枚举移动哪条线段即可。

## Label Matching

题目只需要我们判断是否合法，这就很简单。

我们肯定是优先，非通配符与非通配符匹配，再考虑通配符与非通配符匹配。

用 DSU on tree 维护即可。

## Meeting for Meals

首先我们可以用一次 dijkstra 求出 $t_{\rm meet}$

考虑最短路 DAG，在上面拓扑排序，如果一个点上面已经有多个人，那么我们不需要考虑他；否则，我们更新一下他的答案，这样就能做到线性。