#include<bits/stdc++.h>
struct com{
	int u,v,w;
	bool operator<(const com& b)const{
		return w<b.w;
	}
};
std::vector<com> coms;
const int N=1e5,lgN=std::__lg(N);
int dfn[N],rnk[N],dis[N],dep[N];
using pii=std::pair<int,int>;
pii st[N][lgN];
int n,m;
void makeST(){
	for(int i=1;i<=dfn[0];i++) st[i][0]={dep[rnk[i]],rnk[i]};
	for(int j=1;j<lgN;j++)
		for(int i=1;i+(1<<j)-1<=dfn[0];i++)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
pii getmin(int l,int r){
//	printf("%d %d\n",l,r);
	int k=std::__lg(r-l+1);
	return std::min(st[l][k],st[r-(1<<k)+1][k]);
}
int LCA(int u,int v){
//	printf("lca %d %d\n",u,v);
	return getmin(std::min(dfn[u],dfn[v]),std::max(dfn[u],dfn[v])).second;
}
int getdis(int u,int v){
//	printf("gd %d %d\n",u,v);
	return dis[u]+dis[v]-2*dis[LCA(u,v)];
}
int nx[N],ls[N],to[N],va[N],tot;
void add(int u,int v,int w){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
	va[tot]=w;
}
void dfs(int u,int fa=0){
	rnk[dfn[u]=++dfn[0]]=u;
	for(int i=ls[u],v;i;i=nx[i]){
		if((v=to[i])==fa) continue;
		dis[v]=dis[u]+va[i];
		dep[v]=dep[u]+1;
		dfs(v,u);
		rnk[++dfn[0]]=u;
	}
}
int a[2][N];
namespace SAT{
	std::vector<int> t[N];
	int sta[N],top;
	bool insta[N];
	int dfn[N],low[N];
	int col[N],cnt;
	void clear(int n){
		for(int i=0;i<n;i++) t[i].clear();
		std::fill(dfn,dfn+n,0);
		std::fill(col,col+n,0),cnt=0;
	}
	void addedge(int u,int v){
		t[u].push_back(v);
	}
	void tarjan(int u){
		sta[++top]=u;
		insta[u]=1;
		dfn[u]=low[u]=++dfn[0];
		for(int v:t[u]){
			if(!dfn[v]){
				tarjan(v);
				low[u]=std::min(low[u],low[v]);
			}else if(insta[v])
				low[u]=std::min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			++cnt;
			do{
				col[sta[top]]=cnt;
				insta[sta[top]]=0;
			}while(sta[top--]!=u);
		}
	}
	bool solve(int n){
		for(int i=0;i<n;i++) if(!dfn[i]) tarjan(i);
		for(int i=0;i<n;i+=2) if(col[i]==col[i+1]) return 0;
		return 1;
	}
}
bool check(int mid){
	using namespace SAT;
	clear(2*m);
	for(int i=0;i<mid;i++){
		addedge(coms[i].u,coms[i].v^1),
		addedge(coms[i].v,coms[i].u^1);
	}
	return solve(2*m);
}
int main(){
	freopen("ex_tree1.in","r",stdin);
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		std::fill(ls+1,ls+n+1,0),tot=0;
		for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
		dfs(1);makeST();
		for(int i=1;i<=m;i++) scanf("%d%d",a[0]+i,a[1]+i);
		coms.clear();
//		return 0;
		for(int i=1;i<=m;i++){
			for(int j=i+1;j<=m;j++){
				for(int ii=0;ii<=1;ii++){
					for(int jj=0;jj<=1;jj++){
//						printf("%d~%d : %d\n",a[ii][i],a[jj][j],getdis(a[ii][i],a[jj][j]));
						coms.push_back({(i-1)*2+ii,(j-1)*2+jj,getdis(a[ii][i],a[jj][j])});
					}
				}
			}
		}
		std::sort(coms.begin(),coms.end());
		int left=0,right=coms.size()-1;
		while(left<right){
			int mid=left+right+1>>1;
			if(check(mid)) left=mid;
			else right=mid-1;
		}
		printf("%d\n",coms[left].w);
	}
}
