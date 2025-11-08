#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
const int N=1e5;
std::vector<int> to[N];
std::set<int> tos[N];
int lb[N];bool lbd[N];
int p[N],rk[N];
std::set<std::pair<int,int> > S;
bool vis[N];
std::vector<std::vector<int> > ans;
int main(){
	freopen("friends3.in","r",stdin);
	freopen("friends3.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v),
		to[v].push_back(u),
		tos[u].insert(v),
		tos[v].insert(u);
	for(int i=1;i<=n;i++) S.emplace(lb[i]=0,i);
	for(int i=n;i>=1;i--){
		int u=S.rbegin()->second;
		S.erase(*S.rbegin());
		rk[p[i]=u]=i;lbd[u]=1;
		for(int v:to[u]){
			if(!lbd[v]){
				S.erase({lb[v],v});
				S.emplace(++lb[v],v);
			}
		}
	}
	auto cmp=[](int x,int y){return rk[x]<rk[y];};
	for(int i=1;i<=n;i++)
		std::sort(to[i].begin(),to[i].end(),cmp);
	for(int u=1;u<=n;u++){
		auto it=std::upper_bound(ALL(to[u]),u,cmp);
		if(it==to[u].end()) continue;
		int f=*it;
		for(int v:to[u]){
			if(rk[v]>rk[f]&&tos[f].find(v)==tos[f].end()) goto Not;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[p[i]]){
			ans.push_back(to[p[i]]);
			ans.back().push_back(p[i]);
			for(int v:to[p[i]]) vis[v]=1;
		}
	}
	printf("%llu\n",ans.size());
	for(auto i:ans){
		printf("%llu ",i.size());
		for(int j:i)
			printf("%d ",j);
		puts("");
	}
	fprintf(stderr,"Done!");
	return 0;
	Not:fprintf(stderr,"Sorry. It's NOT a chordal graph!");
}
