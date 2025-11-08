#include<bits/stdc++.h>
#define add(u,v) to[u].push_back(v),to[v].push_back(u)
const int N=1e6+10;
std::vector<int> to[N];
int dep[N],mxd[N];
int dfs1(int u,int fa=0){
	dep[u]=dep[fa]+1;
	int ret=u,tmp;
	for(int v:to[u]){
		if(v==fa) continue;
		if(dep[ret]<dep[tmp=dfs1(v,u)]) ret=tmp;
	}
	return ret;
}
int k;
int dfs2(int u,int fa=0){
	int ret=0;mxd[u]=0;
	for(int v:to[u]){
		if(v==fa) continue;
		ret+=dfs2(v,u);
		mxd[u]=std::max(mxd[u],mxd[v]+1);
	}
	return ret+(mxd[u]>=k);
}
int main(){
	int n;scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<=n;i++) scanf("%d%d",&u,&v),add(u,v);
	dep[0]=-1;
	int s=dfs1(1),h=dep[s],t=dfs1(s),d=dep[t],m=dfs2(1);
	if(h<k) printf("%d",2*(n-1)-std::min(d,k));
	else printf("%d",2*(n+m-2)-(2*h-k));
}