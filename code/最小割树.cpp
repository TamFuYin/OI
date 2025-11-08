#include<bits/stdc++.h>
namespace net{
	const int N=6e2,M=6010;
	int nx[M],ls[N],to[M],ca[M],fl[M],tot=1;
	void addedge(int u,int v,int w){
		nx[++tot]=ls[u];
		to[ls[u]=tot]=v;
		ca[tot]=w;
	}
	void add(int u,int v,int w){
		addedge(u,v,w);
		addedge(v,u,w);
	}
	int dep[N],q[N],cur[N];
	bool bfs(int s,int t){
		memset(dep,0,sizeof dep);
		memcpy(cur,ls,sizeof ls);
		int head=0,tail=1;
		dep[q[1]=s]=1;
		while(head<tail){
			int u=q[++head];
			for(int i=ls[u];i;i=nx[i]){
				if(!dep[to[i]]&&fl[i]<ca[i]){
					dep[to[i]]=dep[u]+1;
					q[++tail]=to[i];
				}
			}
		}
		return dep[t];
	}
	const int INF=1e9;
	int dfs(int u,int t,int flow=INF){
		if(u==t) return flow;
		int ret=0;
		for(int &i=cur[u];i&&flow;i=nx[i]){
			if(dep[to[i]]==dep[u]+1){
				int f=dfs(to[i],t,std::min(flow,ca[i]-fl[i]));
				fl[i]+=f,fl[i^1]-=f,ret+=f,flow-=f;
			}
		}
		return ret;
	}
	int dinic(int s,int t){
		int ret=0;memset(fl,0,sizeof fl);
		while(bfs(s,t)) ret+=dfs(s,t);
		return ret;
	}
}
const int N=1e5,M=1e5;
int nx[M],ls[N],to[M],va[N],tot=1;
void addedge(int u,int v,int w){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	va[tot]=w;
}
void add(int u,int v,int w){
	addedge(u,v,w);
	addedge(v,u,w);
}
void build(std::vector<int> node){
//	for(int i:node) printf("%d ",i);puts("");
	if(node.size()==1) return;
	add(node[0],node[1],net::dinic(node[0],node[1]));
	std::vector<int> s,t;
	for(int i:node){
		if(net::dep[i]) s.push_back(i);
		else t.push_back(i);
	}
	build(s),build(t);
}
const int F=20;
int f[N][F],mn[N][F],dep[N];
void build(int u,int fa=0){
	f[u][0]=fa;
	for(int i=1;i<F;i++){
		f[u][i]=f[f[u][i-1]][i-1];
		mn[u][i]=std::min(mn[u][i-1],mn[f[u][i-1]][i-1]);
	}
	for(int i=ls[u];i;i=nx[i]){
		if(to[i]!=fa){
			dep[to[i]]=dep[u]+1;
			mn[to[i]][0]=va[i];
			build(to[i],u);
		}
	}
}
int solve(int u,int v){
	if(dep[u]<dep[v]) std::swap(u,v);
	int k=dep[u]-dep[v],ret=1e9;
	for(int i=0;i<F;i++){
		if(k&1<<i){
			ret=std::min(ret,mn[u][i]);
			u=f[u][i];
		}
	}
	if(u==v) return ret;
	for(int i=F-1;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			ret=std::min(ret,std::min(mn[u][i],mn[v][i]));
			u=f[u][i],v=f[v][i];
		}
	}
	ret=std::min(ret,std::min(mn[u][0],mn[v][0]));
	return ret;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);++n;
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),++u,++v,net::add(u,v,w);
	std::vector<int> node(n);std::mt19937 myrand(time(0));
	std::iota(node.begin(),node.end(),1);
	std::shuffle(node.begin(),node.end(),myrand);
	build(node);build(1);
	int q;scanf("%d",&q);
	while(q--){
		int u,v;scanf("%d%d",&u,&v);++u,++v;
		printf("%d\n",solve(u,v));
	}
}
