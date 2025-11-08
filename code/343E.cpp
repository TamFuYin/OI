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
using ET=std::tuple<int,int,int>;
std::vector<ET> E;
void build(std::vector<int> node){
	if(node.size()==1) return;
	E.emplace_back(node[0],node[1],net::dinic(node[0],node[1]));
	std::vector<int> s,t;
	for(int i:node){
		if(net::dep[i]) s.push_back(i);
		else t.push_back(i);
	}
	build(s),build(t);
}
bool cmp(ET a,ET b){return std::get<2>(a)>std::get<2>(b);}
const int N=1e5;
int next[N],head[N],tail[N],f[N],sz[N];
int findp(int u){
	if(u==f[u]) return u;
	return f[u]=findp(f[u]);
}
void merge(int u,int v){
	u=findp(u),v=findp(v);
	if(sz[u]<sz[v]) std::swap(u,v);
	f[v]=u;sz[u]+=sz[v];
	next[tail[u]]=head[v];
	tail[u]=tail[v];
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),net::add(u,v,w);
	std::vector<int> node(n);std::mt19937 myrand(time(0));
	std::iota(node.begin(),node.end(),1);
	std::shuffle(node.begin(),node.end(),myrand);
	build(node);std::sort(E.begin(),E.end(),cmp);
	int ans=0;
	std::iota(f+1,f+n+1,1);
	std::iota(head+1,head+n+1,1);
	std::iota(tail+1,tail+n+1,1);
	std::fill(sz+1,sz+n+1,1);
	for(auto e:E){
		int u,v,w;std::tie(u,v,w)=e;
		ans+=w;merge(u,v);
	}
	printf("%d\n",ans);
	for(int p=head[findp(1)];p;p=next[p]) printf("%d ",p);
}
