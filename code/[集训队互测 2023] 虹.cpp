#include<bits/stdc++.h>
#define add(u,v) to[u].push_back(v),to[v].push_back(u)
const int N=8e4+10,B=sqrt(N),lgN=std::__lg(N)+1;
const int X=19901991,Y=20242024;
int n,q;
int z[N];
std::bitset<N> Q[N],cur;
int p[N];
std::bitset<N> vis;
void sieve(){
	for(int i=2;i<=n;i++){
		if(!vis[i]) p[++p[0]]=i;
		for(int j=1;j<=p[0]&&1ll*i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
std::vector<int> qz[N];
int d[N];//current gcd
void dfsZ(int a,int k){
	if(k>p[0]||1ll*a*p[k]>n) return;
	dfsZ(a,k+1);
	a*=p[k];
	for(int b=p[k];a<=n;a*=p[k],b*=p[k]){
		for(int i=b;i<=n;i+=b) cur[i]=z[d[i]*=p[k]]&1;
		for(int i:qz[a]) Q[i]=cur;
//		printf("%d: ",a);
//		for(int i=1;i<=n;i++) printf("%d ",d[i]);puts("");
//		for(int i=1;i<=n;i++) printf("%d",(int)cur[i]);puts("");
		dfsZ(a,k+1);
		if(1ll*a*p[k]>n) break;
	}
	for(int i=p[k];i<=n;i+=p[k]){
		while(d[i]%p[k]==0) d[i]/=p[k];
		cur[i]=z[d[i]]&1;
	}
}
struct operate{int opt,l,r,u;}o[N];
std::vector<int> to[N];
int fa[N],dfncnt,dfn[N*3],rnk[N];
int stmin[N][lgN],stmax[N][lgN],stdfn[N*3][lgN+2];
int LCA(int l,int r){
	int k=std::__lg(r-l+1);
	int L=std::min(stmin[l][k],stmin[r-(1<<k)+1][k]),
	R=std::max(stmax[l][k],stmax[r-(1<<k)+1][k]);
	k=std::__lg(R-L+1);
	return dfn[std::min(stdfn[L][k],stdfn[R-(1<<k)+1][k])];
}
void makeST(){
	for(int i=1;i<=n;i++) stmin[i][0]=stmax[i][0]=rnk[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			stmin[i][j]=std::min(stmin[i][j-1],stmin[i+(1<<j-1)][j-1]),
			stmax[i][j]=std::max(stmax[i][j-1],stmax[i+(1<<j-1)][j-1]);
	for(int i=1;i<=dfncnt;i++) stdfn[i][0]=rnk[dfn[i]];
	for(int j=1;(1<<j)<=dfncnt;j++)
		for(int i=1;i+(1<<j)-1<=dfncnt;i++)
			stdfn[i][j]=std::min(stdfn[i][j-1],stdfn[i+(1<<j-1)][j-1]);
}
std::vector<int> qP[N];
void dfsLCA(int u){
	dfn[rnk[u]=++dfncnt]=u;
	for(int v:to[u]){
		if(fa[u]==v) continue;
		fa[v]=u;dfsLCA(v);
		dfn[++dfncnt]=u;
	}
}
void dfsP(int u){
	cur.set(u);
	for(int i:qP[u]) Q[i]^=cur;
	for(int v:to[u]){
		if(fa[u]==v) continue;
		dfsP(v);
	}
	cur.reset(u);
}
void join(std::bitset<N>& s,int u){
	while(u&&!s[u]) s.set(u),u=fa[u];
}
std::vector<std::pair<int,int> > ql[N],qr[N];
void mo(){
	for(int i=0;i*B+1<=n;i++){
		if(ql[i].empty()) continue;
		std::sort(ql[i].begin(),ql[i].end(),std::greater<std::pair<int,int> >());
		std::sort(qr[i].begin(),qr[i].end());
		int j=(i+1)*B+1;
		cur.reset();
		for(auto p:ql[i]){
			int l,id;std::tie(l,id)=p;
			if(o[id].r<=(i+1)*B) continue;
			while(j>l) join(cur,--j);
			Q[id]=cur;
		}
		j=(i+1)*B;cur.reset();
		for(auto p:qr[i]){
			int r,id;std::tie(r,id)=p;
			if(r<=(i+1)*B) continue;
			while(j<r) join(cur,++j);
			Q[id]|=cur;
		}
		for(auto p:qr[i]){
			int r,id;std::tie(r,id)=p;
			if(r>(i+1)*B) break;
			int l=o[id].l;
			cur.reset();
			for(int j=l;j<=r;j++) join(cur,j);
			Q[id]=cur;
			// printf(">>> id=%d\n",id);
			// for(int j=1;j<=n;j++) printf("%d",(int)cur[j]);puts("");
		}
	}
}
std::bitset<N> n1;
void read(){
	for(int i=1,opt,l,r,u;i<=q;i++){
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1){
			o[i]={opt,l,r};
			int b=(o[i].l-1)/B;
			ql[b].emplace_back(o[i].l,i);
			qr[b].emplace_back(o[i].r,i);
			// printf("%d: %d\n",i,LCA(l,r));
			qP[fa[LCA(l,r)]].push_back(i);
		}
		else{
			scanf("%d",&u),o[i]={opt,l,r,u};
			qz[u].push_back(i);
		}
	}
}
std::bitset<N> W;
void solve(){
	for(int i=1;i<=q;i++){
		const int l=o[i].l,r=o[i].r;
		if(o[i].opt==1){
			W^=Q[i];
//			for(int j=1;j<=n;j++) printf("%d",(int)Q[i][j]);puts("");
		}
		else{
//			for(int j=1;j<=n;j++) printf("%d",(int)Q[i][j]);puts("");
			int t=((((Q[i]&W)>>l)<<l+n-r)&n1).count();
			printf("%d\n",(int)(1ll*X*t%Y+r-l+1-t)%Y);
		}
	}
}
int main(){
//	freopen("data.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",z+i);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v);
	for(int i=1;i<=n;i++) n1.set(i);
	dfsLCA(1);makeST();
	read();
	sieve();
//	greater_prime();
	if(z[1]&1) cur=n1;
	for(int i:qz[1]) Q[i]=cur;
	std::fill(d+1,d+n+1,1);
	dfsZ(1,1);
	mo();cur.reset(),dfsP(1);
	solve();
}
