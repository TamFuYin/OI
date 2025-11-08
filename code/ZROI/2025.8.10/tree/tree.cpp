#include<bits/stdc++.h>
#define add(u,v) to[u].push_back(v)
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
using ll=long long;
const int N=5e2+10,MOD=998244353;
int Add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
int Sub(int x,int y){return x<y?x-y+MOD:x-y;}
void Pls(int& x,int y){x=Add(x,y);}
void Dec(int& x,int y){x=Sub(x,y);}
int Mul(int x,int y){return (ll)x*y%MOD;}
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=Mul(ret,a);
		a=Mul(a,a);b>>=1;
	}
	return ret;
}
std::vector<int> to[N];
int siz[N];
int n,m;
int getC(){
	for(int u=1;u<=n;u++){
		int mx=0;
		for(int v:to[u])
			ckmax(mx,siz[v]>siz[u]?n-siz[u]:siz[v]);
		if(mx<=n/2) return u;
	}
	return 0;
}
void makesiz(int u,int fa=0){
	siz[u]=1;
	for(int v:to[u]){
		if(v==fa) continue;
		makesiz(v,u);
		siz[u]+=siz[v];
	}
}
int fac[N+1],inv[N];
int rt[2],rfa[2];
void getchain(){
	for(int u=1;u<=n;u++){
		for(int v:to[u]){
			if((siz[v]>siz[u]?n-siz[u]:siz[v])==m){
				int x=rt[0]?1:0;
				rt[x]=v,rfa[x]=u;
			}
		}
	}
}
int dfn[N],sub[N];
void dfs(int u,int fa=0){
	siz[u]=1;
	dfn[++dfn[0]]=u;
	sub[u]=1;
	for(int v:to[u]){
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		sub[u]=Mul(sub[u],sub[v]);
	}
	sub[u]=Mul(sub[u],inv[siz[u]]);
}
int f[N][N][N];
int main(){
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=Mul(fac[i-1],i);
	inv[1]=1;
	for(int i=2;i<N;i++) inv[i]=Mul(MOD-MOD/i,inv[MOD%i]);
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	if(2*m<=n){
		makesiz(1),getchain();
//		printf("%d %d\n",rt[0],rt[1]);
		if(!rt[1]){
			puts("0");
			return 0;
		}
		int u=rfa[0],las=rt[0];
		while(u!=rt[1]){
			if(to[u].size()!=2){
				puts("0");
				return 0;
			}
			int nex=to[u][to[u][0]==las];
			las=u,u=nex;
		}
		if(las!=rfa[1]){
			puts("0");
			return 0;
		}
		dfs(rt[0],rfa[0]),dfs(rt[1],rfa[1]);
		int ret=Mul(sub[rt[0]],sub[rt[1]]);
		printf("%d",Mul(ret*2,Mul(fac[m],fac[m])));
	}else{
		makesiz(1);int rt=getC();
		dfs(rt);//printf("%d\n",rt);
		f[1][0][0]=1;
		for(int i=1;i<=n;i++){
//			printf("%d(%d,siz=%d,%d):\n",i,dfn[i],siz[dfn[i]],sub[dfn[i]]);
			for(int j=0;j<=n-m;j++){
				for(int k=0;k<=n-m;k++){
//					printf("f[%d,%d,%d] = %d\n",i,j,k,f[i][j][k]);
					Pls(f[i+1][j][k],f[i][j][k]);
					if(j+siz[dfn[i]]<=n-m)
						Pls(f[i+siz[dfn[i]]][j+siz[dfn[i]]][k],Mul(f[i][j][k],sub[dfn[i]]));
					if(k+siz[dfn[i]]<=n-m)
						Pls(f[i+siz[dfn[i]]][j][k+siz[dfn[i]]],Mul(f[i][j][k],sub[dfn[i]]));
				}
			}
		}
//		int ans=0;
//		for(int j=0;j<=n-m;j++)
//			Pls(ans,Mul(f[n+1][j][2*(n-m)-j],Mul(fac[j],fac[2*(n-m)-j])));
		printf("%d",Mul(Mul(f[n+1][n-m][n-m],Mul(fac[n-m],fac[n-m])),fac[m*2-n]));
	}
}
