#include<bits/stdc++.h>
const int N=1e3,M=2e3;
struct graph{
	std::vector<int> to[N];
}g[N];
bool vis[N];
int dis[N];
int q[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1,u,v,w;i<=m;i++)
			scanf("%d%d%d",&u,&v,&w),g[w].to[u].push_back(v);
		for(int s=1;s<=n;s++){
			std::fill(dis+1,dis+n+1,1e9);
			
			for(int i=0;i<n;i++){
				int head=0,tail=1;
				dis[s]=0;q.emplace(0,s);
				while(head<tail){
					int u=q[++head];
					for(int v:g[i].to[u])
						if(!vis[v]) vis[q[++tail]=v]=1;
				}
			}
		}
	}
}