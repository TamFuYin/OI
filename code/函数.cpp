#include<bits/stdc++.h>
const int N=5e2;
std::map<double,int> f[N+10][N+10];
int g[N+10][N+10];
int main(){
	f[0][0][0]=1;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			for(int x=1;x<=i&&x<=10;x++){
				for(int y=1;y<=j&&y<=10;y++){
					double k=1.*y/x;
					for(auto p:f[i-x][j-y]){
						if(p.first<k){
							if(f[i][j].find(k)==f[i][j].end()) f[i][j][k]=p.second+1;
							else f[i][j][k]=std::max(f[i][j][k],p.second+1);
						}
					}
				}
			}
			for(auto p:f[i][j]) g[i][j]=std::max(g[i][j],p.second);
		}
	}
	// int T;scanf("%d",&T);
	// while(T--){
		// int n,m;scanf("%d%d",&n,&m);
		// printf("%d\n",g[n][m]);
	// }
}
