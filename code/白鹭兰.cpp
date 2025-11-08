#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
const int N=2e5+10;
int dfn[N],low[N];
std::vector<int> G[N],T[N];
int sta[N],top,tot;
void tarjan(int u){
	dfn[u]=low[u]=++dfn[0];
	sta[++top]=u;
	for(int v:G[u]){
		if(!dfn[v]){
			tarjan(v);
			ckmin(low[u],low[v]);
			if(low[v]>=dfn[u]){
				T[u].push_back(++tot);
				T[tot].push_back(u);
				do T[tot].push_back(sta[top]),
				T[sta[top]].push_back(tot);
				while(sta[top--]!=v);
			}
		}
		else ckmin(low[u],dfn[v]);
	}
}
int siz[N],n,rt;
void makes(int u,int fa=0){
	siz[u]=u<=n;
	for(int v:T[u]){
		if(v==fa) continue;
		makes(v,u);
		siz[u]+=siz[v];
	}
}
template<typename T>
struct mxsc{
	T mx,sc;
	void ck(T a){
		if(a>mx) sc=mx,mx=a;
		else if(a>sc) sc=a;
	}
};
using pii=std::pair<int,int>;
mxsc<pii> tmp;
std::vector<int> vec,pth;
void dfsp(int u,int fa=0){
	vec.push_back(u);
	pii mx={0,0};
	for(int v:T[u]){
		if(v==fa) continue;
		ckmax(mx,std::make_pair(siz[v],v));
	}
	if(mx.second) dfsp(mx.second,u);
}
bool vis[N];
void dfs(int u,int fa=0){
	if(u<=n) vec.push_back(u);
	vis[u]=1;
	for(int v:T[u]){
		if(vis[v]) continue;
		dfs(v,u);
	}
}
std::vector<int> with[N];
std::vector<int> ans;
int mx;
namespace bpl{
	bool in[N];
	int fa[N],deg[N],dfn[N],low[N],rnk[N];
	std::vector<int> lis[N];
	void tarjan(int u){
		// printf("TARJAN %d\n",u);
		rnk[dfn[u]=low[u]=++dfn[0]]=u;
		for(int v:G[u]){
			if(!in[v]) continue;
			if(!dfn[v]){
				fa[v]=u;++deg[u];
				tarjan(v);
				ckmin(low[u],low[v]);
			}
			else ckmin(low[u],dfn[v]);
		}
		lis[fa[u]].push_back(u);
		lis[rnk[low[u]]].push_back(u);
	}
	bool del[N];
	void proc(int u){
//		fprintf(stderr,">>> %d\n",u);
		ans.push_back(u);
		del[u]=1;
		for(int v:lis[u]) if(!del[v]) proc(v);
	}
	std::vector<int> pat;
	void bipolar(std::vector<int>& V,int s,int t){
		dfn[0]=0;fa[s]=0;
		for(int i:V) lis[i].clear(),dfn[i]=0,in[i]=1;
//		 for(int i:V) fprintf(stderr,"%d ",i);fprintf(stderr,"\n");
//		 fprintf(stderr,"%d->%d\n",s,t);
		tarjan(s);pat.clear();
		for(int u=t;u;u=fa[u]) pat.push_back(u),del[u]=1;
		std::reverse(pat.begin(),pat.end());
		for(int u:pat) proc(u);
		for(int i:V) in[i]=del[i]=0;
	}
}
int main(){
	freopen("data.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int m;scanf("%d%d",&n,&m);tot=n;
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),
	G[u].push_back(v),G[v].push_back(u);
	tarjan(1);
	// for(int i=1;i<=n;i++) for(int j:T[i]) printf("%d %d\n",i,j);
	makes(1);
	mxsc<int> srt={0,0};
	for(int u=1;u<=tot;u++){
		int mx=n-siz[u];
		for(int v:T[u])
			if(siz[v]<siz[u]) ckmax(mx,siz[v]);
		if(mx<=n/2) ckmax(rt,u),srt.ck(u);
	}
	// printf("%d\n",rt);
	assert(srt.sc<=n);
	makes(rt);
	for(int v:T[rt]) tmp.ck({siz[v],v});
	dfsp(tmp.mx.second,rt);
	std::reverse(vec.begin(),vec.end());
	pth.insert(pth.end(),vec.begin(),vec.end());
	pth.push_back(rt);
	vec.clear();
	dfsp(tmp.sc.second,rt);
	pth.insert(pth.end(),vec.begin(),vec.end());
	for(int i:pth) vis[i]=1;
	vec.clear();
	for(int i=0;i<pth.size();i++) if(pth[i]>n)
		for(int u:T[pth[i]]) if(i==1||u!=pth[i-1])
			dfs(u),std::swap(with[u],vec),ckmax(mx,(int)with[u].size());
	for(int i=0;i<pth.size();i++) if(pth[i]>n){
		bpl::bipolar(T[pth[i]],pth[i-1],pth[i+1]);
		if(i!=pth.size()-2) ans.pop_back();
	}
	printf("%d %d\n",mx,(int)ans.size());
	for(int i:ans){
		printf("%d ",(int)with[i].size());
		for(int j:with[i]) printf("%d ",j);
		puts("");
	}
}
