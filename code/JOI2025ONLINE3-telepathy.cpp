#include"telepathy.h"
const int N=1e5;
#define ckmax(a,b) a=std::max(a,b)
int siz[N];
std::vector<int> to[N];
int size,rt[2];
int dep[N],mxd;
void centroid(int u,int fa=0){
	siz[u]=1;
	int mx=0;
	for(int v:to[u]){
		if(v==fa) continue;
		centroid(v,u),siz[u]+=siz[v];
		ckmax(mx,siz[v]);
	}
	if(std::max(mx,size-siz[u])<=size/2) rt[rt[0]!=-1]=u;
}
int fa[N];
void dfs(int u){
	ckmax(mxd,dep[u]);
	for(int v:to[u]){
		if(v==fa[u]) continue;
		dep[v]=dep[u]+1;
		fa[v]=u;dfs(v);
	}
}
std::vector<int> ans;
#include<bits/stdc++.h>
std::vector<int> Aitana(int n,std::vector<int> A,std::vector<int> B,int S,int subtask){
	for(int i=0;i<n;i++) to[i].clear();
	for(int i=0;i<n-1;i++) to[A[i]].push_back(B[i]),to[B[i]].push_back(A[i]);
	size=n;rt[0]=rt[1]=-1;centroid(0);mxd=0;
	if(rt[1]!=-1){
		dep[rt[0]]=dep[rt[1]]=0;
		fa[rt[0]]=rt[1],fa[rt[1]]=rt[0];
		dfs(rt[0]);dfs(rt[1]);
	}
	else{
		dep[rt[0]]=0;
		fa[rt[0]]=-1;
		dfs(rt[0]);
	}
	ans.clear();
	int x=S;while(x!=rt[0]&&x!=rt[1]) ans.push_back(x),x=fa[x];
	for(int i=0;i<=mxd-dep[S];i++) ans.push_back(x);
	if(rt[1]!=-1) ans.push_back(rt[x==rt[0]]);
	// for(int i:ans) printf("%d ",i);puts("");
	while(ans.size()!=10*n+1) ans.push_back(x);
	return ans;
}
std::vector<int> Bruno(int n,std::vector<int> A,std::vector<int> B,int S,int subtask){
	for(int i=0;i<n;i++) to[i].clear();
	for(int i=0;i<n-1;i++) to[A[i]].push_back(B[i]),to[B[i]].push_back(A[i]);
	size=n;rt[0]=rt[1]=-1;centroid(0);mxd=0;
	if(rt[1]!=-1){
		dep[rt[0]]=dep[rt[1]]=0;
		fa[rt[0]]=rt[1],fa[rt[1]]=rt[0];
		dfs(rt[0]);dfs(rt[1]);
	}
	else{
		dep[rt[0]]=0;
		fa[rt[0]]=-1;
		dfs(rt[0]);
	}
	ans.clear();
	int x=S;while(x!=rt[0]&&x!=rt[1]) ans.push_back(x),x=fa[x];
	for(int i=0;i<=mxd-dep[S];i++) ans.push_back(x);
	if(rt[1]!=-1) ans.push_back(x);
	// for(int i:ans) printf("%d ",i);puts("");
	while(ans.size()!=10*n+1) ans.push_back(x);
	return ans;
}