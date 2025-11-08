#include<bits/stdc++.h>
const int N=1e5;
int deg[N];
std::vector<int> lis[N];
int main(){
	using ll=long long;
	int T;scanf("%d",&T);
	while(T--){
		int n,m,k,s;scanf("%d%d%d%d",&n,&m,&k,&s);
		for(int i=1;i<=m;i++) deg[i]=0,lis[i].clear();
		ll ans=0;++deg[s];
		for(int i=1,a,b,c;i<=n;i++){
			scanf("%d%d%d",&a,&b,&c);
			++deg[c];--deg[a];lis[a].push_back(-b);
			ans+=b;
		}
		for(int i=1,x;i<=k;i++) scanf("%d",&x),++deg[x];
		for(int i=1;i<=m;i++){
			std::sort(lis[i].begin(),lis[i].end());
			while(deg[i]<0) ans+=lis[i].back(),lis[i].pop_back(),++deg[i];
		}
		printf("%lld\n",ans);
	}
}
