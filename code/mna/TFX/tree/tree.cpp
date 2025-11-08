#include<bits/stdc++.h>
const int N=1e5,lgN=log2(N);
int v[N];
std::vector<int> to[N];
int rs[N][lgN];
int f[N][lgN];
int g[N][lgN];
int last[N],pr[N],dep[N];
void dfs(int u){
	pr[u]=last[dep[u]];last[dep[u]]=u;
	for(int v:to[u]) dep[v]=dep[u]+1,dfs(v);
	rs[u][0]=last[dep[u]+1];
	f[u][0]=f[pr[u]][0]+v[u];
	g[u][0]=g[pr[u]][0]+(v[u]&1?-1:1);
	for(int i=1;i<lgN;i++){
		rs[u][i]=rs[rs[u][i-1]][i-1];
		f[u][i]=f[u][i-1]+f[rs[u][i-1]][i-1]+g[rs[u][i-1]][i-1]-g[rs[u][i]][i-1];
		g[u][i]=g[pr[u]][0]+(v[u]>>i&1?-(1<<i):1<<i)+g[rs[u][0]][i];
	}
}
int solve(int u,int d){
	int x=u,ret=0;
	for(int i=lgN-1;i>=0;i--)
		if(d>>i&1) ret+=f[x][i],x=rs[x][i];
	for(int i=lgN-1;i>=0;i--)
		if(d>>i&1) ret+=g[u][i]-g[x][i],u=rs[u][i];
	return ret;
}
int main(){
	freopen("tree.in","r",stdin);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",v+i);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),to[fa].push_back(i);
	dfs(1);
	int q;scanf("%d",&q);
	while(q--){
		int u,k;scanf("%d%d",&u,&k);
		printf("%d\n",solve(u,k)-solve(pr[u],k));
	}
}
