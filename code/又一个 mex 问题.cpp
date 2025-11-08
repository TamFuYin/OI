#include<bits/stdc++.h>
const int N=2e6+10;
int a[N];
std::vector<int> to[N];
int rd() {
	static char buf[50000000],*p=0;
	if(!p) fread(buf,sizeof(buf),1,stdin),p=buf;
	int x=0;
	for(;!isdigit(*p);) ++p;
	for(;isdigit(*p);++p) x=x*10+((*p)&15);
	return x;
}
unsigned long long myhash(int n,int *f) {
	unsigned long long s=1;
	for(int i=1;i<=n;++i) s^=s<<13,s^=s>>7,s^=s<<17,s+=f[i]+1;
	return s;
}
int maxt[N],dfn;
int ans[N];
void dfs(int u){
	int cur=++dfn;
	maxt[a[u]]=cur;
	for(int v:to[u]) dfs(v),ans[u]=std::max(ans[u],ans[v]);
	while(maxt[ans[u]]>=cur) ++ans[u];
}
int main(){
//	freopen("ex_a4.in","r",stdin);
	int n=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=2;i<=n;i++) to[rd()].push_back(i);
	dfs(1);printf("%llu",myhash(n,ans));
}
