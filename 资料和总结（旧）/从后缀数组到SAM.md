# 从后缀数组到SAM

处理关于子串的字符串问题的强大工具。

## 后缀数组

#### 定义章

sa[i]：排名为i的后缀的起始下标.

rk[i]：起始下标为i的后缀的排名.

容易看出rk[sa[i]]=sa[rk[i]]=i.

#### 解法章

利用倍增和基数排序，我们有O(nlogn)的计算sa和rk的算法。

[![img](https://oi-wiki.org/string/images/sa2.png)](https://wenku.baidu.com/view/5b886b1ea76e58fafab00374.html)

```c++
bool cmp(int x,int y,int w)
{return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];}
void SA(char s[])
{
	int n=strlen(s+1);int m=127;//m是rk的值域
	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;//一个字符的大小可以看作他的排名.因为我们的rk要求相同的排名要相同，但不要求最简
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];//计数排序
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;//相同字符，排在后面的排名要大(我也不造为什么)
	for(int w=1,rank;;w<<=1,m=rank)//w是当前要连接的两个"后缀"的下标差
	{
		rank=0;for(int i=n;i>n-w;i--) id[++rank]=i;//因为[n-w+1,n]的第二关键字为0，理当排在先前
		for(int i=1;i<=n;i++)//id[i]是第二关键字的排名为i的第一关键字的下标
		if(sa[i]>w) id[++rank]=sa[i]-w;//利用旧的sa
		memset(cnt,0,sizeof cnt);//key1[i]是第二关键字的排名为i的第一关键字的非最简"排名"
		for(int i=1;i<=n;i++) cnt[key1[i]=rk[id[i]]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[key1[i]]--]=id[i];//sa[第一关键字的排名]=第一关键字的下标，且第二关键字大的排后边
		memset(oldrk+1,rk+1,n*sizeof(int));
		rank=0;for(int i=1;i<=n;i++)
		rk[sa[i]]=cmp(sa[i],sa[i-1],w)?rank:++rank;
		if(rank==n)
		{
			for(int i=1;i<=n;i++)
			sa[rk[i]]=i;
			break;
		}
	}
}
```

#### 应用章

* 最小循环移动同构串[(字符加密)](https://www.luogu.com.cn/problem/P4051)：倍长，然后就是后缀排序问题了。
* 在线查找子串。预处理主串的sa，查询时二分即可。O(|S|log|S|+|T|log|S|)（在S中寻找T）

## height

#### 定义章

记LCP(S,T)为串S,T的最长公共前缀的长度。

lcp(i,j)=LCP([i,n],[j,n])

height[i]=lcp(sa[i],sa[i-1])即排名i和i-1的前缀的最长公共前缀的长度

height[1]=0

有height[rk[i]]≥height[rk[i-1]]-1

#### 解法章

利用上述定理有O(n)解法。

```c++
void make_height(char s[])
{
	for(int i=1,j=0;i<=n;i++)
	{
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		height[rk[i]]=k;
	}
}
```

#### 应用章

$$
lcp(sa[i],sa[j])=\min_{i<k\le j}height[k]
$$

