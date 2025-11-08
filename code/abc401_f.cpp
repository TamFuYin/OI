#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=2e5+10;
using ll=long long;
std::vector<int> g1[N],g2[N];
int d1[N],d2[N];
int dep[N]={-1};
ll suf[N];
int dfs(std::vector<int> to[],int u,int fa=0){
	static int tmp;
	dep[u]=dep[fa]+1;
	int ret=u;
	for(int v:to[u]){
		if(v==fa) continue;
		if(dep[tmp=dfs(to,v,u)]>dep[ret]) ret=tmp;
	}
	return ret;
}
int main(){
	int n1,n2;scanf("%d",&n1);
	for(int i=1,u,v;i<n1;i++) scanf("%d%d",&u,&v),g1[u].push_back(v),g1[v].push_back(u);
	scanf("%d",&n2);
	for(int i=1,u,v;i<n2;i++) scanf("%d%d",&u,&v),g2[u].push_back(v),g2[v].push_back(u);
	int v,D1=dep[v=dfs(g1,dfs(g1,1))];
	for(int i=1;i<=n1;i++) d1[i]=dep[i];
	dfs(g1,v);
	for(int i=1;i<=n1;i++) ckmax(d1[i],dep[i]);	
	int D2=dep[v=dfs(g2,dfs(g2,1))];
	for(int i=1;i<=n2;i++) d2[i]=dep[i];
	dfs(g2,v);
	for(int i=1;i<=n2;i++) ckmax(d2[i],dep[i]);
	std::sort(d2+1,d2+n2+1);
	for(int i=n2;i>=1;i--) suf[i]=suf[i+1]+d2[i];
	int D=std::max(D1,D2);
	ll ans=0;
	for(int i=1;i<=n1;i++){
		int k=std::lower_bound(d2+1,d2+n2+1,D-d1[i]-1)-d2;
		ans+=1ll*(k-1)*D+suf[k]+1ll*(n2-k+1)*(d1[i]+1);
	}
	printf("%lld",ans);
}
