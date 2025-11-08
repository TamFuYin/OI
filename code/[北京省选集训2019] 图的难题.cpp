/*
森林的充要条件：对于其任意导出子图，都有 $|E|\le |V|-1$
所以可以大胆猜测此题的充要条件是对于任意导出子图都有 $|E|\le 2(|V|-1)$
改成最优化问题即为 $\max(|E|-2|V|)\le -2$
尝试孤立地看待点和边。我们发现「导出子图」的唯一约束是：
如果边选了，那么它的两个端点也一定要选。
边的权值为 1，点的权值为 -2。于是转化为最大权闭合子图问题，用网络流解决即可。
但是有一个问题，这个一定得是一个非空子图，因为空图是不合法的...
所以我们得钦定某个点一定得选，使用删边最大流即可
*/
#include<bits/stdc++.h>
#define _assert(x) ({if(!(x)) printf("Failed at %d",__LINE__),exit(-1);})
namespace NetworkFlow{
	const int N=6e3+5,M=1e5,INF=1e9;
	int nx[M],ls[N],to[M],ca[M],tot,sz;
	void clear(){memset(ls,0,sizeof ls),tot=1;}
	void adds(int u,int v,int c){
		nx[++tot]=ls[u];
		to[ls[u]=tot]=v;
		ca[tot]=c;
	}
	void add(int u,int v,int w=INF){
		adds(u,v,w);
		adds(v,u,0);
	}
	int q[N],dep[N],cur[N];
	bool bfs(int s,int t){
		int head=0,tail=1;
		memset(dep,0,sizeof dep);
		memcpy(cur,ls,sizeof ls);
		dep[q[1]=s]=1;
		while(head<tail){
			int u=q[++head];
			for(int i=ls[u];i;i=nx[i]){
				if(!dep[to[i]]&&ca[i]){
					dep[to[i]]=dep[u]+1;
					q[++tail]=to[i];
				}
			}
		}
		return dep[t]!=0;
	}
	int dfs(int u,int t,int flow=INF){
//		printf("%d %d %d\n",u,t,flow);
		if(u==t) return flow;
		int ret=0;
		for(int& i=cur[u];i&&flow;i=nx[i]){
			if(dep[to[i]]==dep[u]+1){
				int f=dfs(to[i],t,std::min(flow,ca[i]));
				ca[i]-=f,ca[i^1]+=f,flow-=f,ret+=f;
			}
		}
		return ret;
	}
	int dinic(int s,int t){
		int ret=0;
		while(bfs(s,t)) ret+=dfs(s,t);
		return ret;
	}
}
int tmp;
int main(){
	using namespace NetworkFlow;
	int T=1;
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		int s=n+m+1,t=s+1;clear();
		for(int i=1;i<=m;i++) add(s,n+i,1);
		add(1,t,0);for(int i=2;i<=n;i++) add(i,t,2);
		for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(n+i,u),add(n+i,v);
		int res;
		if((res=dinic(s,t))<m) {puts("No");continue;}
		for(int u=2;u<=n;u++){
			dinic(u,s);
			for(int i=ls[u];i;i=nx[i]) if(to[i]==t) res-=ca[i^1],ca[i]=ca[i^1]=0;
			for(int i=ls[u-1];i;i=nx[i]) if(to[i]==t) ca[i]=2;
			if((res+=dinic(s,t))<m) {puts("No");goto Continue;}
		}
		puts("Yes");
		Continue:;
	}
}
