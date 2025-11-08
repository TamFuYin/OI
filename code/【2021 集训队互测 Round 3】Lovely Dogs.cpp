#include<bits/stdc++.h>
const int N=1e5;
int mu[N],mud[N];
std::vector<int> tau[N];
std::vector<int> pr;
bool npr[N];
std::vector<int> to[N];
int siz[N],hson[N],dfn[N],rnk[N];
void dfs0(int u,int fa=0){
	siz[u]=1;
	rnk[dfn[u]=++dfn[0]]=u;
	for(int v:to[u]){
		if(v==fa) continue;
		dfs0(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]])
			hson[u]=v;
	}
}
int a[N],b[N];
std::set<int> s;
using ll=long long;
ll powd1[N];
int d,cur;
void add(int x){
	for(int t:tau[x]) b[t]+=mud[x];
	for(int t:tau[x])
		cur+=mud[x]*mu[t]*b[std::min(powd1[t]/std::__gcd(powd1[t],(ll)x),ll(N-1))];
}
void del(int x){
	for(int t:tau[x])
		cur-=mud[x]*mu[t]*b[std::min(powd1[t]/std::__gcd(powd1[t],(ll)x),ll(N-1))];
	for(int t:tau[x]) b[t]-=mud[x];
}
int ans[N];
void dsu(int u,int fa=0){
	for(int v:to[u]){
		if(v==fa||v==hson[u]) continue;
		dsu(v,u);
		for(int i=dfn[v];i<dfn[v]+siz[v];i++)
			del(a[rnk[i]]);
	}
	if(hson[u]) dsu(hson[u],u);
	for(int v:to[u]){
		if(v==fa||v==hson[u]) continue;
		for(int i=dfn[v];i<dfn[v]+siz[v];i++)
			add(a[rnk[i]]);
	}
	add(a[u]);
	ans[u]=cur;
}
ll qpow(ll a,int b){
	if(pow(a,b)>=1e11) return 0;
	ll ret=1;
	while(b){
		if(b&1) ret*=a;
		a*=a;b>>=1;
	}
	return ret;
}
int main(){
	mu[1]=mud[1]=1;
	for(int i=2;i<N;i++){
		if(!npr[i]) pr.push_back(i),mud[i]=mu[i]=-1;
		for(int j:pr){
			if(1ll*i*j>=N) break;
			mud[i*j]=-mud[i];
			npr[i*j]=1;
			if(i%j==0) break;
			mu[i*j]=-mu[i];
		}
	}
	for(int i=1;i<N;i++){
		for(int j=1;1ll*i*j<N;j++)
			tau[i*j].push_back(i);
	}
	int n;scanf("%d%d",&n,&d);
	for(int i=1;i<N;i++) powd1[i]=qpow(i,d+1);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v),
		to[v].push_back(u);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	dfs0(1);dsu(1);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
}
