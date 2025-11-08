#include<bits/stdc++.h>
using ll=long long;
const int N=1e5,M=1e5;
int nx[M],ls[N],to[M],va[M],mnv[M],mxv[M],tot;
bool type[M];
void add(int u,int v,int l,int r){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	mnv[tot]=l;mxv[tot]=r;
}
int n,s0,s1,t;
struct elem{
	int u;
	ll dis;
	bool tag;
	bool operator<(const elem& b)const{
		return dis>b.dis;
	}
};
std::priority_queue<elem> q;
ll dis[N][2];
bool vis[N][2];
void dijkstra(bool b){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	q.push({s0,dis[s0][0]=0,0});
	q.push({s1,dis[s1][1]=0,1});
	for(int i=1;i<=tot;i++) va[i]=mxv[i];
	while(!q.empty()){
		int u=q.top().u;bool t=q.top().tag;q.pop();
		if(vis[u][t]) continue;
		vis[u][t]=1;
		for(int i=ls[u],v;i;i=nx[i]){
			if(dis[u][0]<dis[u][1]) va[i]=mnv[i];
			else if(dis[u][0]>dis[u][1]) va[i]=mxv[i];
			else va[i]=b?mnv[i]:mxv[i];
			if(dis[u][t]+va[i]<dis[v=to[i]][t]){
				dis[v][t]=dis[u][t]+va[i];
				q.push({v,dis[v][t],t});
			}
		}
	}
}
int main(){
	int m,k;
	scanf("%d%d%d%d%d%d",&n,&m,&k,&s0,&s1,&t);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),
		add(u,v,w,w);
	for(int i=1,u,v,l,r;i<=k;i++)
		scanf("%d%d%d%d",&u,&v,&l,&r),
		add(u,v,l,r);
	dijkstra(0);
	if(dis[t][0]<dis[t][1]){
		puts("WIN");
		for(int i=m+1;i<=m+k;i++) printf("%d ",va[i]);
		return 0;
	}
	else if(dis[t][0]==dis[t][1]){
		puts("DRAW");
		for(int i=m+1;i<=m+k;i++) printf("%d ",va[i]);
		return 0;
	}
	dijkstra(1);
	if(dis[t][0]==dis[t][1]){
		puts("DRAW");
		for(int i=m+1;i<=m+k;i++) printf("%d ",va[i]);
		return 0;
	}
	else{
		puts("LOSE");
		return 0;
	}
}