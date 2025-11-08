/*
关于我每次做网络流的题都想不到网络流（想到了也不会建模）这件事
*/
#include<bits/stdc++.h>
namespace net{
	const int N=1e4+10,M=4e4+10;
	int nx[M],ls[N],to[M],ca[M],va[M],tot=1;
	void addedge(int u,int v,int c,int w){
		nx[++tot]=ls[u];
		to[ls[u]=tot]=v;
		ca[tot]=c;
		va[tot]=w;
	}
	void add(int u,int v,int c,int w){
		addedge(u,v,c,w);
		addedge(v,u,0,-w);
	}
	int cur[N],q[N*100],dis[N],ans;
	bool vis[N];
	int dfs(int u,int t,int flow=INT_MAX){
		if(u==t) return flow;
		int ret=0;vis[u]=1;
//		printf("DFS %d\n",u);
		for(int& i=cur[u];i&&flow;i=nx[i]){
			if(!vis[to[i]]&&dis[to[i]]==dis[u]+va[i]){
				int f=dfs(to[i],t,std::min(flow,ca[i]));
				ca[i]-=f,ca[i^1]+=f,flow-=f,ret+=f;ans+=f*va[i];
			}
		}
		vis[u]=0;
		return ret;
	}
	bool spfa(int s,int t){
		memset(dis,0x3f,sizeof dis);
		memcpy(cur,ls,sizeof ls);
		int head=0,tail=1;dis[q[1]=s]=0;
		while(head<tail){
			int u=q[++head];vis[u]=0;
			for(int i=ls[u];i;i=nx[i]){
				if(ca[i]&&dis[to[i]]>dis[u]+va[i]){
					dis[to[i]]=dis[u]+va[i];
					if(!vis[to[i]]) vis[q[++tail]=to[i]]=1;
				}
			}
		}
		return dis[t]!=0x3f3f3f3f;
	}
	int dinic(int s,int t){
		int ret=0;
		while(spfa(s,t)) ret+=dfs(s,t);
		return ret;
	}
}
const int N=1e5;
int w[N],a[N],last[N],sum;
int main(){
	freopen("ex_pet3.in","r",stdin);
//	freopen("pet.out","w",stdout);
	int m,n,k,_k;scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	for(int i=1,tmp;i<=k;i++) scanf("%d",&tmp),tmp==a[_k]?0:a[++_k]=tmp;
	k=_k;
	for(int i=1;i<=k;i++) sum+=w[a[i]];
	for(int i=1;i<=k;i++){
		if(last[a[i]]) net::add(last[a[i]]+1,i,1,-w[a[i]]);
		last[a[i]]=i;
		net::add(i,i+1,INT_MAX,0);
	}
	net::add(k+2,1,m-1,0);
	net::dinic(k+2,k+1);
	printf("%d%d\n",sum,net::ans);
	printf("%d",sum+net::ans);
}
