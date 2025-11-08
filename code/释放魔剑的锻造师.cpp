#include<bits/stdc++.h>
const int N=5e4+10,M=1e5+10;
using ull=unsigned long long;
ull g[M],f[N];//g[i] 表示区间包含 i 的询问集合，f[i] 表示能到达 i 的询问集合
std::vector<int> a[M],da[M];
int s[N],t[N];
int ls[N],to[M],nx[M],tot;
void add(int u,int v){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
}
int n;
int q[N],ind[N];
void topo(){
	for(int i=1;i<=n;i++)
		for(int j=ls[i];j;j=nx[j])
			++ind[to[j]];
	int head=0,tail=0;
	for(int i=1;i<=n;i++) if(!ind[i]) q[++tail]=i;
	while(head<tail){
		int u=q[++head];
		for(int i=ls[u];i;i=nx[i])
			if(!--ind[to[i]])
				q[++tail]=to[i];
	}
}
void solve(){
	for(int i=1;i<=n;i++)
		for(int j=ls[q[i]];j;j=nx[j])
			f[to[j]]|=f[q[i]]&g[j];
}
int main(){
	int m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v);
	topo();
	for(int i=0,l,r;q--;i++){
		scanf("%d%d%d%d",s+i,t+i,&l,&r);
		a[l].push_back(i);
		da[r+1].push_back(i);
		f[s[i]]|=1ull<<i;
		if(i==63||!q){
			ull cur=0;
			for(int j=1;j<=m;j++){
				for(int k:a[j]) cur^=1ull<<k;
				for(int k:da[j]) cur^=1ull<<k;
				g[j]=cur;a[j].clear(),da[j].clear();
			}
			solve();
			for(int j=0;j<=i;j++) puts(f[t[j]]>>j&1?"YES":"NO");
			i=-1;memset(f,0,sizeof f);
		}
	}
}