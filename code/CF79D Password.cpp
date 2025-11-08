#include<bits/stdc++.h>
#define add(u,v) to[u].push_back(v),to[v].push_back(u)
const int N=1e6,K=21;
bool goal[N];
int x[N];
std::vector<int> to[N];
int dis[K+1][N];
#define ckmin(a,b) a=std::min(a,b)
int n;
const int INF=1e9;
void bfs(int* dis,int s){
	static int q[N];
	int head=0,tail=1;
	std::fill(dis+1,dis+n+2,INF);
	dis[q[1]=s]=0;
	while(head<tail){
		int u=q[++head];
		for(int v:to[u]){
			if(dis[v]==INF){
				q[++tail]=v;
				dis[v]=dis[u]+1;
			}
		}
	}
}
int f[1<<K];
int main(){
	int k,l;scanf("%d%d%d",&n,&k,&l);
	for(int i=1;i<=k;i++) scanf("%d",x+i),goal[x[i]]=1;
	for(int i=n+1;i>=1;i--) goal[i]^=goal[i-1];
	k=0;for(int i=1;i<=n+1;i++) if(goal[i]) x[k++]=i;
	// printf("%d\n",k);
	for(int i=1,a;i<=l;i++){
		scanf("%d",&a);
		for(int j=1;j+a-1<=n;j++) add(j,j+a);
	}
	for(int i=0;i<k;i++) bfs(dis[i],x[i]);
	std::fill(f,f+(1<<k),INF);
	f[0]=0;
	for(int s=0;s<(1<<k);s++){
		for(int i=0;i<k;i++) if(s>>i&1){
			for(int j=i+1;j<k;j++) if(s>>j&1){
				ckmin(f[s],f[s^1<<i^1<<j]+dis[i][x[j]]);
			}
		}
		// printf("%d: %d\n",s,f[s]);
	}
	printf("%d",f[(1<<k)-1]==INF?-1:f[(1<<k)-1]);
}