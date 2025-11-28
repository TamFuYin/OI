# Berlekamp Massey Algorithm

这么有用的算法赛前不复习真是对不住啊

问题：给定数列 $\{a\}_n$，求一个最短的递推式 $\{f\}_m$ 满足 $a_i=\sum_{j=0}^{m-1} a_{i-j-1}f_j$。

大致思想是：增量维护当前的最短递推式，每次发现不满足条件的时候就更改，记 $F_i$ 为满足对于所有 $m\le k\le i$ 都满足 $a_k=\sum_{j=0}^{m-1}a_{k-j-1}f_j$ 的最短的 $f$。

初始时可以令 $F_{m-1}=()$

记 $\Delta_i=a_i-\sum_{j=0}^{m-1}a_{i-j-1}F_{i-1,j}$。

如果 $\Delta_i=0$，则 $F_i=F_{i-1}$。

否则，此时我们非增长 $F$ 不可。

如果这是我们的第一次修改，也就是说 $F_{i-1}=()$，则说明 $a_i$ 是这个序列的第一个非零项，则我们怎么搞都肯定不行，所以可以令 $F_i=(\overbrace{0,0,\dots,0}^{i+1\text{ 个 }0})$

否则考虑找到一个长度为 $m$ 的 $g$ 满足对于所有 $m\le k<i$ 都有 $\sum_{j=0}^{m-1} a_{k-j-1}g_j=0$，而 $\sum _{j=0}^{m-1} a_{i-j-1}g_j\ne 0$。

显然我令 $g_j=-f_{j-1}，g_0=1$ 即可完成前一项任务，但是对于后一项却一定不满足，因为 $F_{i-1}$ 在 $i-1$ 上是合法的。

我们考虑找到上一次 $F$ 变化的位置，即 $F_{l-1}\ne F_l=F_{i-1}$。然后令 $G=(\overbrace{0,0,\dots,0}^{i-l-1\text{ 个 }0},1,-F_{l-1})$。这样就对了，因为我们保证 $F_{l-1}$ 在 $l$ 不合法，且得到的就是 $\Delta_l$。

然后我们令 $F_i=F_{i-1}+\frac{\Delta_i}{\Delta_l}G$ 即可

但是这里似乎是错的，我们只有在 $|G|>|F|$ 的时候才能把它纳入「上一个解」中。

用 `std::basic_string<int>` 写出来很短

```c++

using poly=std::basic_string<int>;
poly BM(poly a){
    poly f,fl;int l=-1,dell;
    for(int i=0;i<a.size();i++){
        int del=a[i];
        for(int j=0;j<f.size();j++) (del+=MOD-1ll*a[i-j-1]*f[j]%MOD)%=MOD;
        if(del==0) continue;
        if(l==-1) f=poly(i+1,0),l=i,dell=del;
        else{
            poly g=poly(i-l-1,0)+(MOD-1)+fl;
            int k=MOD-1ll*del*qpow(dell,MOD-2)%MOD;
            if(g.size()>f.size()) fl=f,l=i,dell=del;
            f.resize(std::max(f.size(),g.size()));
            for(int i=0;i<g.size();i++) (f[i]+=1ll*k*g[i]%MOD)%=MOD;
        }
    }
    return f;
}
```