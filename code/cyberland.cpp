#include<bits/stdc++.h>
const int D=70,N=1e5+10,M=2e5+10;
using vi=std::vector<int>;
bool mvis[D][N];
double dis[D][N];
struct data{
	int dep;
	double dis;
	int id;
	bool operator<(const data& b)const{
		return !(dep<b.dep||dep==b.dep&&dis<=b.dis);
	}
};
std::priority_queue<data> pq;
int nx[M],ls[N],to[M],va[M],tot;
void add(int u,int v,int w){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	va[tot]=w;
}
bool vis[N];
int q[N];
double solve(int n,int m,int k,int h,vi x,vi y,vi c,vi arr){
	k=std::min(k,D-1);
	tot=0,memset(ls,0,sizeof(ls));
	for(int i=0;i<m;i++) add(x[i],y[i],c[i]),add(y[i],x[i],c[i]);
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=k;i++)
		std::fill(dis[i],dis[i]+n,INFINITY),
		std::fill(mvis[i],mvis[i]+n,0);
	int head=0,tail=1;vis[q[1]=0]=1;
	while(head<tail){
		int u=q[++head];
		if(u==0||arr[u]==0) pq.push({0,dis[0][u]=0,u});
		for(int i=ls[u];i;i=nx[i])
			if(!vis[to[i]]&&to[i]!=h)
				vis[q[++tail]=to[i]]=1;
	}
	double ans=INFINITY;
	while(!pq.empty()){
		int d=pq.top().dep,u=pq.top().id;pq.pop();
		if(mvis[d][u]) continue;
		mvis[d][u]=1;
		if(u==h){
			ans=std::min(ans,dis[d][u]);
			continue;
		}
		for(int i=ls[u];i;i=nx[i]){
			if(dis[d][to[i]]>dis[d][u]+va[i])
				pq.push({d,dis[d][to[i]]=dis[d][u]+va[i],to[i]});
		}
		if(arr[u]==2&&d!=k&&dis[d+1][u]>dis[d][u]/2) pq.push({d+1,dis[d+1][u]=dis[d][u]/2,u});
	}
	return ans==INFINITY?-1:ans;
}
