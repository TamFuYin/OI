#include<bits/stdc++.h>
namespace F
{
	const int N=5e4+10,M=5e6+10,INF=(1ll<<31)-1;
	int ls[N],to[M*2],nx[M*2],cst[M*2],cap[M*2],cur[M*2],edge=1;
	void add(int u,int v,int capacity,int cost)
	{
		nx[++edge]=ls[u];
		to[ls[u]=edge]=v;
		cap[edge]=capacity;
		cst[edge]=cost;
	}
	void addedge(int u,int v,int capacity,int cost)
	{
		add(u,v,capacity,cost);
		add(v,u,0,-cost);
	}
	int mincost;
	int q[N];bool vis[N];
#define ll long long
	ll dis[N];
	bool SPFA(int s,int t)
	{
		memset(dis,0x3f,sizeof dis);
		memcpy(cur,ls,sizeof ls);
		int head=0,tail=1;
		vis[q[1]=s]=1;dis[s]=0;
		while(head<tail)
		{
			int u=q[++head];vis[u]=0;
//			printf("%d\n",u);
			for(int i=ls[u];i;i=nx[i])
			{
				int v=to[i];
				if(cap[i]&&dis[v]>dis[u]+cst[i])
				{
					dis[v]=dis[u]+cst[i];
					if(!vis[v]) q[++tail]=v,vis[v]=1;
				}
			}
		}
		return dis[t]<INF;
	}
	int min(int a,int b) {return a<b?a:b;}
	int dfs(int u,int t,ll flow=INF)
	{
//		printf("|%d\n",u);
		if(u==t||flow==0) return flow;
		vis[u]=1;ll ret=0;
		for(int &i=cur[u];i&&flow;i=nx[i])
		{
			int v=to[i];
			if(!vis[v]&&cap[i]&&dis[v]==dis[u]+cst[i])
			{
				ll f=dfs(v,t,min(cap[i],flow));
				mincost+=f*cst[i];
//				printf("|%d %d %d\n",f,cst[i],mincost);
				cap[i]-=f;cap[i^1]+=f;
				ret+=f;flow-=f;
			}
		}
		vis[u]=0;return ret;
	}
	int dinic(int s,int t)
	{
		int ret=0,tmp;
		while(SPFA(s,t))
			while(tmp=dfs(s,t))
				ret+=tmp;//,printf("%d\n",ret);
		return ret;
	}
	void clear(int n){
		std::fill(ls+1,ls+n+1,0);
		edge=1;mincost=0;
	}
}
const int N=1e5;
int c[N],b[N];
int main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",c+i);
		for(int i=1;i<=n;i++) scanf("%d",b+i);
		int s=n+1,t=n+2;
		F::clear(n+2);
		for(int i=1;i<=n;i++)
			if(!b[i]) F::addedge(s,i,1,0);
			else F::addedge(i,t,1,0);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(!b[i]&&b[j])
					F::addedge(i,j,1,-int(c[i]==c[j]));
			}
		}
		F::dinic(s,t);
		printf("%d\n",-F::mincost);
	}
}
