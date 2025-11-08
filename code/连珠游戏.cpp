#include<bits/stdc++.h>
const int N=2e5+10;
int nx[N*2],ls[N],to[N*2],va[N*2],tot;
void add(int u,int v,int w){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	va[tot]=w;
}
using ll=long long;
ll f[N],g[N];
struct pair{
	ll max,sec;
	pair():max(INT_MIN),sec(INT_MIN){};
	void ckmax(ll x){
		if(x>max) sec=max,max=x;
		else if(x>sec) sec=x;
	}
};
void dfs(int u,int fa=0){
	pair tmp;ll all=0;
	for(int i=ls[u],v;i;i=nx[i]){
		if((v=to[i])==fa) continue;
		dfs(v,u);
		all+=std::max(va[i]+g[v],f[v]);
		tmp.ckmax(va[i]+f[v]-std::max(va[i]+g[v],f[v]));
	}
	if(!to[ls[u]]) f[u]=0,g[u]=INT_MIN;
	else f[u]=all+std::max(0ll,tmp.max+tmp.sec),g[u]=all+tmp.max;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),
		add(u,v,w),add(v,u,w);
	dfs(1);
	printf("%lld",f[1]);
}