#include<bits/stdc++.h>
const int N=1e6+10;
bool vis[N];
int p[N];
using pii=std::pair<int,int>;
std::vector<std::vector<pii> > ans;
std::vector<pii> tmp;
void circ(int i){
	vis[i]=vis[p[i]]=1;
	tmp.emplace_back(i,p[i]);
	if(!vis[p[p[i]]]) circ(p[p[i]]);
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",p+i);
	while(1){
		bool OK=0;
		tmp.clear();
		for(int i=1;i<=n;i++) if(p[i]!=i) OK=1;
		if(!OK) break;
		std::fill(vis+1,vis+n+1,0);
		for(int i=1;i<=n;i++) if(!vis[i]&&!vis[p[i]]&&i!=p[i]) circ(i);
		for(auto i:tmp) std::swap(p[i.first],p[i.second]);
		ans.push_back(tmp);
	}
	printf("%llu\n",ans.size());
	for(auto v:ans){
		printf("%llu\n",v.size());
		for(auto p:v)
			printf("%d %d\n",p.first,p.second);
	}
}