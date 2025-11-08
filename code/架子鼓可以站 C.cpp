#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=2e5+10;
std::vector<int> to[N];
int f[N];//子树直径
int mxd[N];
struct pair{
	int max,sec;
	pair(int max=-114514,int sec=-114514):max(max),sec(sec){}
	void max_eq(int x){
		if(x>max) sec=max,max=x;
		else if(x>sec) sec=x;
	}
};
pair max(const pair& a,const pair& b){
	static int tmp[4]={a.max,a.sec,b.max,b.sec};
	std::sort(tmp,tmp+4);
	return {tmp[3],tmp[2]};
}
void dfs(int u){
	pair tmp;
	mxd[u]=f[u]=0;
	for(int v:to[u]){
		// dep[v]=dep[u]+1;
		dfs(v);
		ckmax(f[u],f[v]);
		tmp.max_eq(mxd[v]);
		ckmax(mxd[u],mxd[v]+1);
	}
	ckmax(f[u],tmp.max+tmp.sec+2);
	ckmax(f[u],mxd[u]);
}
int g[N];//删掉子树后的同根儿子子树的直径
int h[N];//只能走父亲的直径
pair pre[N],suf[N];
int pre2[N],suf2[N];
#define pit *std::prev(it)
int ans;
void dfs2(int u){
	// printf("%d g=%d f=%d\n",u,g[u],f[u]);
	ckmax(ans,g[u]+f[u]+2);
	if(to[u].empty()) return;
	pre[*to[u].begin()]=suf[*to[u].rbegin()]={};
	pre2[*to[u].begin()]=suf2[*to[u].rbegin()]=0;
	for(auto it=++to[u].begin();it!=to[u].end();it++){
		pre[*it]=pre[pit];
		pre2[*it]=pre2[pit];
		pre[*it].max_eq(mxd[pit]);
		ckmax(pre2[*it],f[pit]);
	}
	for(auto it=++to[u].rbegin();it!=to[u].rend();it++){
		suf[*it]=suf[pit];
		suf2[*it]=suf2[pit];
		suf[*it].max_eq(mxd[pit]);
		ckmax(suf2[*it],f[pit]);
	}
	for(int v:to[u]){
		pair tmp=max(pre[v],suf[v]);
		g[v]=std::max(std::max(g[u],h[u]+(tmp.max<0?0:tmp.max+1)),
		std::max(tmp.max+tmp.sec+2,std::max(pre2[v],suf2[v])));
		h[v]=std::max(h[u]+1,tmp.max+2);
		dfs2(v);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) to[i].clear();
		for(int i=2,fa;i<=n;i++)
			scanf("%d",&fa),to[fa].push_back(i);
		dfs(1);
		ans=f[1];
		pair tmp;
		for(int v:to[1]){
			tmp.max_eq(f[v]);
			g[v]=-1,h[v]=0;
			dfs2(v);
		}
		ckmax(ans,tmp.max+tmp.sec+2);
		printf("%d\n",ans);
	}
}
