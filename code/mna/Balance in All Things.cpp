#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k, P;
vector<ll> fac, ifac;

// 快速幂取模
int modpow(int a, int e) {
	ll r=1, x=a;
	while(e){
		if(e&1) r=r*x%P;
		x=x*x%P;
		e>>=1;
	}
	return (int)r;
}
// 预处理阶乘和逆元
void init_comb(int N){
	fac.assign(N+1,1);
	for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%P;
	ifac.assign(N+1,1);
	ifac[N]=modpow(fac[N],P-2);
	for(int i=N;i>0;i--) ifac[i-1]=ifac[i]*i%P;
}
int C(int a,int b){
	if(b<0||b>a) return 0;
	return fac[a]*ifac[b]%P*ifac[a-b]%P;
}

// 状态映射
map<array<int,7>,int> sid;
vector<array<int,7>> states;
// 转移表
vector<vector<pair<int,int>>> trans;

// 检查分布合法
bool valid(const array<int,7>& a){
	int sum=0, cnt=0;
	for(int i=0;i<7;i++){
		cnt+=a[i];
		sum+=a[i]*(i-3);
		if(a[i]<0) return false;
	}
	return cnt==2*n && sum==0;
}

// 多重递归：逐对(s,t)枚举配对数  
void dfs_pair(int idx,
	array<int,7>& cur,
	array<int,7>& nxt_cnt,
	int used_pairs,
	ll ways,
	int u){
		static const vector<pair<int,int>> pairs = [](){
			vector<pair<int,int>> v;
			for(int s=0;s<7;s++)
				for(int t=s;t<7;t++)
					v.emplace_back(s,t);
			return v;
		}();
		int M = pairs.size();
		if(idx==M){
			if(used_pairs!=n) return;
			// 构造下一个状态
			array<int,7> b = cur;
			// 对所有 s,t，根据 nxt_cnt 计算 b'
			for(int i=0;i<7;i++){
				b[i] += nxt_cnt[i];
			}
			if(!valid(b)) return;
			int v = sid.count(b) ? sid[b] : (sid[b]=states.size(), states.push_back(b));
			trans[u].emplace_back(v, (int)(ways%P));
			return;
		}
		auto [s,t] = pairs[idx];
		int max_m = (s==t? cur[s]/2 : min(cur[s],cur[t]));
		// 枚举配对数 m
		for(int m=0; m<=max_m; m++){
			int rem = used_pairs + m;
			if(rem > n) break;
			// 计算选这 m 对的组合数
			ll w2 = ways;
			if(s==t){
				w2 = w2 * C(cur[s] - 2*(m-1), 2) % P * modpow(1,0) % P;  
				// 具体计算：从 cur[s] 人中选 2m 人，两两配对，总方案数应用双阶乘
				// (这里仅示意，请根据组合数公式调整)
			} else {
				w2 = w2 * (ll)C(cur[s], m) % P * C(cur[t], m) % P * fac[m] % P;
			}
			// 更新 nxt_cnt
			// 胜负后，s 减 m（或减 2m），t 同理，胜者得+1，败者-1 => 更新 nxt_cnt 对应分数
			// 细节请自行补全
			dfs_pair(idx+1, cur, nxt_cnt, rem, w2, u);
			// 回溯 nxt_cnt、ways
		}
	}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin>>n>>k>>P;
	init_comb(2*n);
	
	array<int,7> start = {0,0,0,2*n,0,0,0};
	sid[start]=0;
	states.push_back(start);
	queue<array<int,7>> q;
	q.push(start);
	
	// BFS 枚举可达状态并构造转移
	while(!q.empty()){
		auto cur = q.front(); q.pop();
		int u = sid[cur];
		// 为 u 分配转移容器
		// cur 为当前分布，启动枚举
		array<int,7> nxt_cnt = {};
		dfs_pair(0, cur, nxt_cnt, 0, 1, u);
		// 将新发现状态入队
		for(auto &pr : trans[u]){
			if(pr.first >= (int)states.size()-1){
				q.push(states.back());
			}
		}
	}
	
	int S = states.size();
	vector<int> dp(S), dp2(S);
	dp[0]=1;
	
	// k 轮 DP
	for(int step=0; step<k; step++){
		fill(dp2.begin(), dp2.end(), 0);
		for(int u=0;u<S;u++){
			if(!dp[u]) continue;
			for(auto &e: trans[u]){
				dp2[e.first] = (dp2[e.first] + (ll)dp[u]*e.second)%P;
			}
		}
		dp.swap(dp2);
	}
	
	int ans=0;
	for(int x: dp) ans=(ans+x)%P;
	cout<<ans<<"\n";
	return 0;
}

