#include<bits/stdc++.h>
#define _assert(x) if(!(x)) printf("RE at LINE %d",__LINE__),exit(-1)
const int N=2e5+10;
using ll=long long;
using pll=std::pair<ll,ll>;
std::vector<pll> f[N],g[2],tmp;
int to[N][2],v[N];
int n;
bool check(ll mid){
	for(int i=1;i<=n;i++) f[i].clear();
	for(int i=n;i>=1;i--){
		if(!to[i][0]) {f[i].emplace_back(0,0);continue;}
		g[0].clear(),g[1].clear();
		for(int s=0;s<2;s++){
			int l=to[i][0^s],r=to[i][1^s];
			for(int j=0,k=0;j<f[l].size();j++){
				while(k<f[r].size()&&f[l][j].second+f[r][k].first+v[l]+v[r]>mid) ++k;
				if(k==f[r].size()) break;
				g[s].emplace_back(f[l][j].first+v[l],f[r][k].second+v[r]);
			}
		}
		f[i].resize(g[0].size()+g[1].size());
		std::merge(g[0].begin(),g[0].end(),g[1].begin(),g[1].end(),f[i].begin(),
		[](const pll& a,const pll& b){return a.first>b.first||a.first==b.first&&a.second<b.second;});
		tmp.clear();
		for(int j=0;j<f[i].size();j++) if(!j||f[i][j-1].first!=f[i][j].first) tmp.push_back(f[i][j]);
		f[i].clear();
		for(auto p:tmp) f[i].push_back(p);
	}
	return !f[1].empty();
}
int main(){
	scanf("%d",&n);
	for(int i=2,p;i<=n;i++){
		scanf("%d%d",&p,v+i);
		(!to[p][0]?to[p][0]:to[p][1])=i;
	}
	ll left=0,right=1e10;
	while(left<right){
		ll mid=left+right>>1;
		if(check(mid)) right=mid;
		else left=mid+1;
	}
	printf("%lld",left);
}
