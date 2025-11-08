#include<bits/stdc++.h>
const int M=4e5+10,N=2e5+10;
using ll=long long;
int tot=1,nx[M],ls[N],to[M],va[M];
void add(int u,int v,int w){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	va[tot]=w;
}
ll dis[2][N];
bool vis[N];
int n;
int p[N],ebh[M];
bool onp[N];
void dijkstra(int s,ll dis[]){
	static std::priority_queue<std::pair<ll,int> > Q;
	std::fill(dis+1,dis+n+1,1e18);
	std::fill(vis+1,vis+n+1,0);
	Q.emplace(dis[s]=0,s);
	while(!Q.empty()){
		int u=Q.top().second;Q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=ls[u];i;i=nx[i]){
			if(dis[to[i]]>dis[u]+va[i])
				dis[to[i]]=dis[u]+va[i],
				Q.emplace(-dis[to[i]],to[i]);
		}
	}
}
int l[N],r[N];
ll ans[N];
std::vector<ll> ins[N],era[N];
std::multiset<ll> S;
std::pair<ll,int> ord[N];
int main(){
	int m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	dijkstra(1,dis[0]);
	dijkstra(n,dis[1]);
	ll D=dis[0][n];
	int pn=0;p[++pn]=1;
	while(p[pn]!=n){
//		printf("%d\n",p[pn]);
		for(int i=ls[p[pn]];i;i=nx[i])
			if(dis[0][to[i]]==dis[0][p[pn]]+va[i]
			&&dis[0][to[i]]+dis[1][to[i]]==D){
				ebh[i/2]=pn;
				p[++pn]=to[i];
				break;
			}
	}
	memset(l,0x3f,sizeof l);
	for(int i=1;i<=pn;i++) l[p[i]]=r[p[i]]=i,onp[p[i]]=1;
	for(int i=1;i<=n;i++) ord[i]={dis[0][i],i};
	std::sort(ord+1,ord+n+1);
	for(int i=1;i<=n;i++){
		int u=ord[i].second;
		for(int j=ls[u];j;j=nx[j]){
			if(!onp[to[j]]&&dis[0][to[j]]==dis[0][u]+va[j])
				l[to[j]]=std::min(l[to[j]],l[u]);
		}
	}
	for(int i=1;i<=n;i++) ord[i]={dis[1][i],i};
	std::sort(ord+1,ord+n+1);
	for(int i=1;i<=n;i++){
		int u=ord[i].second;
		for(int j=ls[u];j;j=nx[j]){
			if(!onp[to[j]]&&dis[1][to[j]]==dis[1][u]+va[j])
				r[to[j]]=std::max(r[to[j]],r[u]);
		}
	}
	for(int i=2;i<=tot;i++){
		if(!ebh[i/2]
		// dis[0][to[i^1]]+va[i]!=dis[0][to[i]]
		){
			int L=l[to[i^1]],R=r[to[i]];
			ll d=dis[0][to[i^1]]+va[i]+dis[1][to[i]];
			// printf(">>> %d,%d %d from %d,%d\n",L,R,d,to[i^1],to[i]);
			if(L>=R) continue;
			ins[L].push_back(d);
			era[R].push_back(d);
		}
	}
	for(int i=1;i<pn;i++){
//		printf("!");
		for(int v:era[i]) /*printf("ERASE %d\n",v),*/S.erase(S.lower_bound(v));
		for(int v:ins[i]) /*printf("INSERT %d\n",v),*/S.insert(v);
		ans[i]=S.empty()?INT_MAX:*S.begin();
	}
	// for(int i=1;i<=pn;i++) printf("%d ",p[i]);puts("");
	while(q--){
		int t,x;scanf("%d%d",&t,&x);
		int u=to[t*2],v=to[t*2+1];
		printf("%lld\n",ebh[t]?std::min(D-va[t*2]+x,ans[ebh[t]]):std::min(D,
		std::min(dis[0][u]+x+dis[1][v],dis[0][v]+x+dis[1][u])));
	}
}
