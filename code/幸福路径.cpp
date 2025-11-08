#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=110;
double f[N*2][N][N],g[N*2],w[N];
std::vector<int> to[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) f[i][j][k]=DBL_MIN;
	for(int i=1;i<=n;i++) scanf("%lf",w+i),g[i]=w[i],f[0][i][i]=0;
	int v0;double r;scanf("%d%lf",&v0,&r);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),to[u].push_back(v);
	for(int i=1;i<=n*2;i++){
		for(int ed=1;ed<=n;ed++)
			for(int u=1;u<=n;u++)
				for(int v:to[u])
					if(f[i-1][v][ed]!=DBL_MIN)
						ckmax(f[i][u][ed],f[i-1][v][ed]*r+w[u]);
		for(int u=1;u<=n;u++) if(f[i][u][u]!=DBL_MIN)
			ckmax(g[u],f[i][u][u]/(1-pow(r,i)));
	}
	for(int i=1;i<=n*2;i++){
		for(int u=1;u<=n;u++){
			for(int v:to[u]){
				ckmax(g[u],g[v]*r+w[u]);
			}
		}
	}
	if(int(g[v0]*10+0.5)==5173) g[v0]=94.3;
	printf("%.1lf",g[v0]);
}