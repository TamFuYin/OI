#include<bits/stdc++.h>
#include"diameter.h"
using pii=std::pair<int,int>;
template<typename T>
bool find(typename std::vector<T>::iterator b,typename std::vector<T>::iterator e,T& x){
	auto i=std::lower_bound(b,e,x);
	return i!=e&&*i==x;
}
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
#define mp std::make_pair
pii find_diameter(int task_id,int n){
	if(n==1) return {1,1};
	if(n==2) return {1,2};
	std::vector<int> path,d1(n+1),d2(n+1);
	//d1: x 到链 1~2 的距离,d2: x 到边 1~v 的距离
	pii u={INT_MAX,0};
	for(int i=3;i<=n;i++){
		d1[i]=query(1,2,i)/2;
		ckmin(u,mp(d1[i],i));
	}
	int l=u.first,v;
	if(!in(u.second,1,2)) v=2,l=1;
	for(int i=3;i<=n;i++)
		if(!(d1[i]-=l)) path.push_back(i);
	if(l>1){
		std::sort(path.begin(),path.end());
		int tmp=*path.begin();path.erase(path.begin());
		pii mx(0,2);
		int min=INT_MAX;
		for(int i:path){
			int dmx=query(2,tmp,i)/2;
			ckmax(mx,mp(dmx,i));
			ckmin(min,dmx);
		}
		if(min==mx.first) v=tmp;
		else v=mx.second;
	}
	pii mxd={l-1,2};
	for(int i=3;i<=n;i++)
		if(!find(path.begin(),path.end(),i)&&i!=v)
			d2[i]=query(1,v,i)/2-1,ckmax(mxd,mp(d2[i],i));
	int x=mxd.second;
	if(x==v) return {1,2};
	auto type=[&](int u){return u!=2&&d1[u]==d2[u]+l;};
	mxd={d2[x]+1,type(x)?v:1};
	if(type(x)) ckmax(mxd,mp(d2[x]+l,2));
	else ckmax(mxd,mp(d1[x]*2+l-(d2[x]+1),2));
//	printf("%d\n",d2[24]+d2[23]+1);
	for(int i=3,co=type(x)?1:v;i<=n;i++)
		if(!find(path.begin(),path.end(),i)&&i!=v&&i!=x){
			if(type(x)^type(i)) ckmax(mxd,mp(d2[x]+d2[i]+1,i));
			else ckmax(mxd,mp(query(co,x,i)-d2[x]-d2[i],i));
		}
	int y=mxd.second;
//	printf("%d %d %d %d\n",l,v,x,y);
//	printf("d=%d\n",mxd.first);
	return {x,y};
}
// ________________________________________________________________________
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "diameter.h"

namespace {
	static void WA(std::string err) {
		std::cout << "WA: " << err << std::endl;
		exit(0);
	}
	
	static const int N = 2e5 + 10;
	static int subid, n;
	static std::vector<int> e[N];
	
	static int fa[N], dep[N], cnt, p[N], pos[N], l[N], r[N];
	static void dfs(int u) {
		p[++cnt] = u, pos[u] = cnt;
		dep[u] = dep[fa[u]] + 1;
		l[u] = cnt;
		for (auto v : e[u])
			if (v != fa[u]) {
				fa[v] = u, dfs(v);
				p[++cnt] = u;
			}
		r[u] = cnt;
	}
	
	static int lg[N];
	static std::pair<int, int> mn[N][20];
	static void init() {
		cnt = 0, dfs(1), lg[0] = -1;
		for (int i = 1; i <= cnt; i++) {
			mn[i][0] = std::make_pair(dep[p[i]], p[i]);
			lg[i] = lg[i >> 1] + 1;
		}
		for (int j = 1; j <= lg[cnt]; j++) {
			for (int i = 1; i <= cnt - (1 << j) + 1; i++) {
				mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	static int LCA(int x, int y) {
		int l = pos[x], r = pos[y];
		if (l > r) std::swap(l, r);
		int tmp = lg[r - l + 1];
		return std::min(mn[l][tmp], mn[r - (1 << tmp) + 1][tmp]).second;
	}
	
	static int cntq2;
	static int cntq1;
	
	static int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }
	
	static void solve() {
		cntq1 = cntq2 = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) e[i].clear();
		for (int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
		init();
		std::pair<int, int> ans = find_diameter(subid, n);
		int x = 1, y = 1;
		for (int i = 1; i <= n; i++)
			if (dis(x, i) > dis(x, y)) y = i;
		x = y, y = 1;
		for (int i = 1; i <= n; i++)
			if (dis(x, i) > dis(x, y)) y = i;
		if (ans.first < 1 || ans.first > n) {
			WA("find wrong diameter!");
		}
		if (ans.second < 1 || ans.second > n) {
			WA("find wrong diameter!");
		}
		if (dis(x, y) != dis(ans.first, ans.second)) {
			WA("find wrong diameter!");
		}
	}
}  // namespace
bool in(int x, int y, int z) {
	if (x < 1 || x > n) WA("ask2 format error");
	if (y < 1 || y > n) WA("ask2 format error");
	if (z < 1 || z > n) WA("ask2 format error");
	++cntq2;
	if (cntq2 > 2) {
		WA("too many ask2");
	}
	int cnt = 0;
	if (pos[y] >= l[x] && pos[y] <= r[x]) ++cnt;
	if (pos[z] >= l[x] && pos[z] <= r[x]) ++cnt;
	if (cnt == 1) return 1;
	return LCA(y, z) == x;
}

int query(int x, int y, int z) {
	if (x == y || y == z || x == z) WA("ask1 format error");
	if (x < 1 || x > n) WA("ask1 format error");
	if (y < 1 || y > n) WA("ask1 format error");
	if (z < 1 || z > n) WA("ask1 format error");
	++cntq1;
	if (cntq1 > 300000) {
		WA("too many ask1");
	}
	return dis(x, y) + dis(x, z) + dis(y, z);
}
int main() {
	freopen(".in","r",stdin);
	int T;
	scanf("%d%d", &subid, &T);
	while (T--) solve();
	puts("correct");
}
