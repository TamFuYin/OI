#include<bits/stdc++.h>
int S,T,n;
namespace net{
	const int N=2e2+10,M=2e4;
	int nx[M],ls[N],to[M],ca[M],fl[M],tot=1;
	void addedge(int u,int v,int w){
		nx[++tot]=ls[u];
		to[ls[u]=tot]=v;
		ca[tot]=w;
	}
	void add(int u,int v,int w){
		addedge(u,v,w);
		addedge(v,u,0);
	}
	int dep[N],q[N],cur[N];
	bool del[N];
	bool bfs(){
		memset(dep,0,sizeof dep);
		memcpy(cur,ls,sizeof ls);
		int head=0,tail=1;
		dep[q[1]=S]=1;
		while(head<tail){
			int u=q[++head];
			for(int i=ls[u];i;i=nx[i]){
				if(!dep[to[i]]&&!del[to[i]]&&fl[i]<ca[i]){
					dep[to[i]]=dep[u]+1;
					q[++tail]=to[i];
				}
			}
		}
		return dep[T];
	}
	const int INF=1e9;
	int dfs(int u,int flow=INF){
		if(u==T) return flow;
		int ret=0;//printf("dfs %d\n",u);
		for(int &i=cur[u];i&&flow;i=nx[i]){
			if(dep[to[i]]==dep[u]+1){
				int f=dfs(to[i],std::min(flow,ca[i]-fl[i]));
				fl[i]+=f,fl[i^1]-=f,ret+=f,flow-=f;
			}
		}
		return ret;
	}
	int dinic(){
		int ret=0;memset(fl,0,sizeof fl);
		while(bfs()) ret+=dfs(S);
		return ret;
	}
	int remove(int u){
		int ret=0;
		if(!del[u]) del[u]=1,++ret;
		if(!del[u+n]) del[u+n]=1,++ret;
		for(int i=ls[u];i;i=nx[i]){
			if(to[i]!=S&&to[i]!=T){
				if(!del[to[i]]) del[to[i]]=1,++ret;
				if(!del[to[i]-n]) del[to[i]-n]=1,++ret;
			}
		}
		for(int i=ls[u+n];i;i=nx[i]){
			if(to[i]!=S&&to[i]!=T){
				if(!del[to[i]]) del[to[i]]=1,++ret;
				if(!del[to[i]+n]) del[to[i]+n]=1,++ret;
			}
		}
		return ret;
	}
	void recover(int u){
		del[u]=0;
		del[u+n]=0;
		for(int i=ls[u];i;i=nx[i]){
			if(to[i]!=S&&to[i]!=T){
				del[to[i]]=0;
				del[to[i]-n]=0;
			}
		}
		for(int i=ls[u+n];i;i=nx[i]){
			if(to[i]!=S&&to[i]!=T){
				del[to[i]]=0;
				del[to[i]+n]=0;
			}
		}
	}
}
const int N=1e3;
bool mp[N][N];
bool usb[N],ch[N];
int main(){
	int m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),mp[u][v]=1;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				mp[i][j]|=mp[i][k]&mp[k][j];
			}
		}
	}
	S=2*n+1,T=2*n+2;
	for(int i=1;i<=n;i++){
		net::add(S,i,1);
		net::add(n+i,T,1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]){
				net::add(i,n+j,1);
			}
		}
	}
	int k=n-net::dinic();
	printf("%d\n",k);
	std::set<int> ans;
	for(int i=1;i<=n;i++){
		if(n-net::remove(i)/2-net::dinic()==k-1)
			usb[i]=1,ans.insert(i);
		net::recover(i);
	}
	while(!ans.empty()){
		int u=*ans.begin();
		ch[u]=1;ans.erase(u);
		for(int i=net::ls[u];i;i=net::nx[i]){
			if(ans.find(net::to[i]-n)!=ans.end()){
				ans.erase(net::to[i]-n);
			}
		}
		for(int i=net::ls[u+n];i;i=net::nx[i]){
			if(ans.find(net::to[i])!=ans.end()){
				ans.erase(net::to[i]);
			}
		}
	}
	for(int i=1;i<=n;i++) putchar(ch[i]?'1':'0');puts("");
	for(int i=1;i<=n;i++) putchar(usb[i]?'1':'0');
}
