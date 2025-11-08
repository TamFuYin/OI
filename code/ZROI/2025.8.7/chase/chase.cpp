#include<bits/stdc++.h>
const int N=1e6;
std::vector<int> to[N];
#define add(u,v) to[u].push_back(v)
#define ckmax(u,v) u=std::max(u,v)
int g[N];
struct tfx{
	int max,sec,cnt;
	void ck(int x){
		if(x>max) sec=max,max=x,cnt=1;
		else if(x==max) ++cnt;
		else if(x>sec) sec=x;
	}
	int bes(int x){
		if(x==max&&cnt==1) return sec;
		return max;
	}
}f[N];
void dfs(int u,int fa=0){
	f[u]={0,INT_MIN,1};
	for(int v:to[u]){
		if(v==fa) continue;
		dfs(v,u);
		f[u].ck(f[v].max+1);
	}
}
void dfs2(int u,int fa=0){
	for(int v:to[u]){
		if(v==fa) continue;
		g[v]=std::max(g[u],f[u].bes(f[v].max+1))+1;
		dfs2(v,u);
	}
}
int geth(int u,int v){
	return f[v].max>f[u].max?f[u].max:g[v]-1;
}
int main(){
	freopen("chase.in","r",stdin);
	freopen("chase.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) to[i].clear();
		for(int i=1,u,v;i<n;i++)
			scanf("%d%d",&u,&v),
			add(u,v),add(v,u);
		dfs(1),g[1]=0,dfs2(1);
//		for(int i=1;i<=n;i++) printf(">>> %d %d\n",f[i],g[i]);
		for(int i=1;i<=n;i++){
			bool alice=1;
			for(int j:to[i])
				alice&=geth(i,j)>geth(j,i);
			if(alice) {puts("Alice");goto Continue;}
		}
		puts("Bob");
		Continue:;
	}
}
