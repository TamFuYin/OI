# Codeforces Round 1053 (Div. 1)

VP。其实本来由于台风「桦加沙」而在家的，不过由于太困了就没做。

每道题都有 bgm 推荐就很好

## A. Incremental Path

直接模拟即可，最多只用回退一次操作。

## B. Grid Counting

前言：由于垃圾翻译没把 exactly 翻出来导致我赛时没能想出来。

我们令 $x'=\max(x,y),y'=\max(x,n+1-y)$ 那么相当于求一个合法排列数，且有用的点都满足 $x'+y'\ge n+1$。

不难发现，这样实际上只有一种排列！即所有 $x'+y'=n+1$。

对所有 $x'+y'=n+1$，它包含 $x\le \min(x',y')$ 的行，它可以从这 $\min(x',y')$ 个备选点中挑一个，互不相关，所以可以乘法原理。

那么对于每个行限制 $k$，要求 $x'\in [\min(k,n+1-k),\max(k,n+1-k)]$ 中选了的点的个数 $=a_k$。

显然这里要求 $a_k=a_{n+1-k}$。我们从最严格的 $n/2$ 开始，做一下差分就行了。

## C. Limited Edition Shop

~~首先不劣于 $\sum_i v_i$。~~

~~按 Alice 排序后前几个 $v_i\ge 0$ 的先给她选了不会更劣。~~

由于顺序没什么影响，不妨按 Alice 排序。

首先考虑 Alice 能选择的子集 $S$ 满足的条件：对于 $i\in N\backslash S,j\in S,i<j$ 都满足 $b_i<b_j$。

也就是说，只要我们不选 $i$，那么往后你再想选一个 $j$ 都得满足 $b_j>b_i$。

DP 记录当前最严格的限制，用线段树维护转移即可。

## D. Attraction Theory

考虑合法的最终位置数组 $p$ 满足的条件。

观察 1：每个人的相对位置顺序不变。

观察 2：一定是一个前缀把 $p$ 变大，一个后缀把 $p$ 减少。

观察 3：令 $p_i'=p_i+a_i$，那么对任意 $i$，$a_i-a_{i+1}\ge 0$ 且为偶数。

不难发现，满足
- $a_i-a_{i+1}\ge 0$ 且为偶数
- $a_i-a_{i+1}\le p_{i+1}-p_i$

即可。

由于确定了差分和第一个元素就能确定整个数组，所以就做完了。

## E1. Hidden Single (Version 1)

考虑随机一个子集查询，那么对于一个 $x$ 如果出现一次，返回 yes 的概率为 $\frac12$，否则为 $\frac34$。至少要问 $4$ 次才能看出差异，不太行。

考虑类似线段树地询问。

考虑我们已知区间 $[L,R]$ 内有若干元素，分别对这些元素对着 $[L,mid]$ 和 $[mid+1,R]$ 问一遍。

- 如果在两个区间中都出现了，那么他肯定不是我们要找的。后面在子区间中可以不用问了
- 如果都不出现，这是不可能发生的事情。这意味着如果我们问到 $[L,mid]$ 没有就不用再问了。
- 如果只出现在一个子区间，递归进入。

当 $L=R$ 时就找到了。询问的理论上界应为 $O(n\log n)$。

我们可以先随机打乱一下，此时绝大部分元素都散得比较开所以实际询问可能比较少。

```c++
#include<bits/stdc++.h>
#define DEBUG
#ifdef DEBUG
namespace CF{
    struct buf{
        char _[1<<22],*begin,*end;
        buf():begin(_),end(_){}
        template<typename... Args>
        void write(Args... args){end+=sprintf(end,args...);}
        template<typename... Args>
        void read(const char s[],Args... args){
            int len=0;
            sscanf(begin,(std::string(s)+"%n").c_str(),args...,&len);
            begin+=len;
        }
    }out,in;
    std::vector<int> p;
    std::mt19937 rnd(time(0));
    // std::mt19937 rnd(0);
    int n,k,T;
    void _init(){
        n=300,k=rnd()%n+1;
        p.clear();
        for(int i=1;i<=n;i++){
            p.push_back(i);
            if(i!=k) p.push_back(i);
        }
        std::shuffle(p.begin(),p.end(),rnd);
        in.write("%d\n",n);
    }
    void work(){
        char s[3];
        out.read("%s",s);
        if(s[0]=='?'){
            bool ret=0;
            int x,m,k;out.read("%d%d",&x,&m);
            while(m--) out.read("%d",&k),ret|=p[k-1]==x;
            in.write("%d\n",ret);
        }
        else{
            assert(s[0]=='!');
            int x;out.read("%d",&x);
            assert(x==k);
            if(--T) _init();
        }
    }
    __attribute__((constructor))
    void init(){
        T=1;
        in.write("%d\n",T);
        _init();
    }
    #define scanf(s,...) CF::in.read(s,__VA_ARGS__)
    #define printf(...) CF::out.write(__VA_ARGS__)
    #define puts(s) CF::out.write((std::string(s)+'\n').c_str())
    #define fflush(stdout) CF::work()
}
#endif
const int N=1e5+10;
int bh[N],p[N];
bool ans[N];
bool ask(int x,int L,int R){
    printf("? %d %d ",x,R-L+1);
    for(int i=L;i<=R;i++) printf("%d ",bh[i]);
    puts("");fflush(stdout);
    int b;scanf("%d",&b);
    return b;
}
std::vector<int> tl,tr;
bool solve(int L,int R,int l,int r){
    if(l>r) return 0;
    if(L==R){
        assert(l==r);
        printf("! %d\n",p[l]);
        fflush(stdout);
        return 1;
    }
    int mid=L+R>>1;
    for(int i=l;i<=r;i++) ans[i]=ask(p[i],L,mid);
    tl.clear(),tr.clear();
    for(int i=l;i<=r;i++){
        if(ans[i]) {if(!ask(p[i],mid+1,R)) tl.push_back(p[i]);}
        else tr.push_back(p[i]);//,assert(ask(p[i],mid+1,R));
    }
    int ls=tl.size(),rs=tr.size();
    std::copy(tl.begin(),tl.end(),p+l);
    std::copy(tr.begin(),tr.end(),p+l+ls);
    if(solve(L,mid,l,l+ls-1)) return 1;
    return solve(mid+1,R,l+ls,l+ls+rs-1);
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        static std::mt19937 rnd(time(0));
        int m=2*n-1;
        std::iota(bh+1,bh+m+1,1);
        std::shuffle(bh+1,bh+m+1,rnd);
        std::iota(p+1,p+n+1,1);
        assert(solve(1,m,1,n));
    }
}
```

然而并不能过，询问还是太多了。

你注意到一个很显然的事实——包含答案的那个子区间一定是奇数。

然而我们其实并不知道当前区间的真实长度。。。

为什么呢？我们这里直接把同时在区间内和区间外出现的元素踢掉了。但其实它们的位置也是重要的。

我们不妨带上求一下。

然后就能过了，$n=300$ 时平均 $1060$ 左右。

## E2. Hidden Single (Version 2)

Easy Version 的算法跑了若干轮之后，「全部在里面」的元素较少，此时你再去问「有的在里面有的在外面」的元素显得有些蠢。

所以可以在「全部在里面」的元素较少时 跑一下一开始的版本？没必要，我们不需要找到元素的位置。

注意到如果随机选择一个子集，询问 $S$ 和 $U\backslash S$，那么如果两者都是 $1$，那么一定不是我们的答案。询问次数非常少！

## F. Cycle Closing

### 菊花

只需一步。

### 链

考虑第一步把距离为 $2$ 的点先连起来。

记链的长度为 $l=n-1$，那么从 $1$ 到 $n$ 需要走 $\lceil \frac l2\rceil$。

通过跳出去隔一位跳回来，可以对每个点对都构造一条长度为 $\lceil \frac l2\rceil$ 的路径。

### 树

把 $l$ 换成直径长度。

建直径图，公共祖先部分像链一样，向最远的直径端点处延申。

### 一般图

随便找一个生成树即可。

## G. Counting is Fun: The Finale

*Editorial will be out when somebody solves the problem.*