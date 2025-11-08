#include<bits/stdc++.h>
const int N=5e2;
using ld=long double;
std::map<ld,int> f[N+10][N+10];
int g[N+10][N+10];
int main(){
	f[0][0][0]=1;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			f[i][j][(ld)j/i]=2;
			for(int x=1;x<i&&x<=10;x++){
				for(int y=1;y<j&&x+y<=100;y++){
					ld k=(ld)y/x;
					for(auto p:f[i-x][j-y]){
						if(p.first<k){
							if(f[i][j].find(k)==f[i][j].end()) f[i][j][k]=p.second+1;
							else f[i][j][k]=std::max(f[i][j][k],p.second+1);
						}
					}
				}
			}
			for(auto p=++f[i][j].begin();p!=f[i][j].end();p++)
				if(std::prev(p)->second>p->second) ++p,f[i][j].erase(std::prev(p));
			for(auto p:f[i][j]) g[i][j]=std::max(g[i][j],p.second);
//			ld x=-1;
//			for(auto p:f[i][j]) if(p.second==g[i][j]) {x=p.first;break;}
			printf("%2d ",g[i][j]);
		}
		puts("");
	}
	// int T;scanf("%d",&T);
	// while(T--){
		// int n,m;scanf("%d%d",&n,&m);
		// printf("%d\n",g[n][m]);
	// }
}
