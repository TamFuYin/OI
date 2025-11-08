#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ckmax(a,b) a=std::max(a,b)
using ll=long long;
const int N=5e5+10;
int a[N];
std::vector<int> to[N];
int len;
ll ans,cnt;int cur;
int _f[N*5],*fs=_f,*f[N];//f[i,j] 表示以 i 为顶点的和为 j 的路径的数量。
//f0 表示 \sum_{j\ge 0} f[u,j]
int hi[N],son[N];
int bot[N];
void dfs(int u){
	for(int v:to[u]){
		dfs(v);
		if(hi[v]>hi[son[u]]) son[u]=v;
	}
	hi[u]=hi[son[u]]+1;
	bot[u]=son[u]?bot[son[u]]:u;
}
int solve(int u){
	int f0=0,pdu=a[u]<=cur?1:-1;
	if(son[u]){
		f0=solve(son[u]);
		f[u]=f[son[u]]-pdu;
		if(pdu==1) f0+=f[u][0];
		else f0-=f[u][-1];
	}
	++f[u][pdu];
	if(pdu>=0) ++f0;
	for(int v:to[u]){
		if(v==son[u]) continue;
		solve(v);
		for(int j=0,fj=f0;j<=hi[v];fj+=f[u][-(++j)]) cnt+=(ll)fj*f[v][j];
		for(int j=-1,fj=f0-f[u][0];j>=-hi[v];fj-=f[u][-(j--)]) cnt+=(ll)fj*f[v][j];
		for(int i=-hi[v];i<=hi[v];i++){
			f[u][i+pdu]+=f[v][i];
			if(i+pdu>=0) f0+=f[v][i];
		}
	}
//	printf("%d %d\n",u,f0);
	cnt+=f0;return f0;
}
int fa[N];
int main(){
//	freopen("ex_medium5.in","r",stdin);
	int n;scanf("%d",&n);
	for(int i=2;i<=n;i++) scanf("%d",fa+i),to[fa[i]].push_back(i);
	for(int i=1;i<=n;i++) scanf("%d",a+i),a[i]=std::__lg(a[i]+1);
	dfs(1);
	for(int i=1;i<=n;i++) if(son[fa[i]]!=i) f[bot[i]]=fs+2*hi[i],fs+=4*hi[i]+1;
//	for(int i=1;i<=n;i++) printf("bot=%d hi=%d %d\n",bot[i],hi[i],f[i]);
	ll las=0;
//	for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
	for(cur=1;(1<<cur)<=n+1;cur++){
		cnt=0,std::fill(_f,fs,0),solve(1),
		ans+=(cnt-las)*((1<<cur+1)-2),las=cnt;
//		printf("%d : %d\n",cur,cnt);
	}
	printf("%lld",ans);
}
