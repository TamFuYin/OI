#include <bits/stdc++.h>
using ll = long long;
const int N = 500000 + 5;

int n, fa[N], a[N], hi[N], son[N], bot[N];
std::vector<int> to[N];
ll ans, cnt;
int cur;
int _f[N * 5], *fs = _f, *f[N];
std::vector<int> vals;

inline int pd(int u) { return a[u] <= vals[cur] ? 1 : -1; }

void dfs(int u) {
	for (int v : to[u]) {
		dfs(v);
		if (hi[v] > hi[son[u]]) son[u] = v;
	}
	hi[u] = hi[son[u]] + 1;
	bot[u] = son[u] ? bot[son[u]] : u;
}

void solve(int u) {
	if (son[u]) solve(son[u]), f[u] = f[son[u]] - pd(u);
	++f[u][pd(u)];
	for (int v : to[u]) {
		if (v == son[u]) continue;
		solve(v);
		for (int i = -hi[v]; i <= hi[v]; i++)
			cnt += (ll)(f[u][-i + 1] + f[u][-i]) * f[v][i];
		for (int i = -hi[v]; i <= hi[v]; i++)
			f[u][i + pd(u)] += f[v][i];
	}
	cnt += f[u][0] + f[u][1];
}

int main() {
	freopen("ex_medium2.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n;
	for (int i = 2; i <= n; i++) {
		std::cin >> fa[i];
		to[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		// 按题解规则映射
		int k = std::__lg(a[i] + 1);
		a[i] = (1 << (k + 1)) - 2;
		vals.push_back(a[i]);
	}
	std::sort(vals.begin(), vals.end());
	vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
	
	dfs(1);
	// 对每条长链链顶分配空间
	for (int i = 1; i <= n; i++) {
		if (son[fa[i]] != i) {
			f[bot[i]] = fs + 2 * hi[i];
			fs += 4 * hi[i] + 1;
		}
	}
	
	for (cur = 0; cur < (int)vals.size(); cur++) {
		cnt = 0;
		std::fill(_f, fs, 0);
		solve(1);
		ans += cnt * vals[cur];
	}
	std::cout << ans << "\n";
}

