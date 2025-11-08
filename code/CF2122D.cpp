#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){
	a=std::min(a,b);
}
const int N=5e3+10;
std::vector<int> to[N];
int f[N][2];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			to[i].clear();
		for(int i=1,u,v;i<=m;i++)
			scanf("%d%d",&u,&v),
			to[u].push_back(v),
			to[v].push_back(u);
		f[1][0]=0;
		for(int i=2;i<=n;i++) f[i][0]=1e9;
		for(int t=0;t<=3*n;t++){
			if(f[n][t&1]<1e9){
				printf("%d %d\n",t,f[n][t&1]);
				break;
			}
			for(int u=1;u<=n;u++)
				f[u][t+1&1]=f[u][t&1]+1;
			for(int u=1;u<=n;u++)
				ckmin(f[to[u][t%to[u].size()]][t+1&1],f[u][t&1]);
		}
	}
}
