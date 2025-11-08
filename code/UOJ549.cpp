#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int N=6e4+10;
int f[N][9][1<<4],g[N][9],a[N];
int main(){
	int n,k;scanf("%d%d",&n,&k);
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	g[0][0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		for(int j=1;j<=k;j++){
			for(int s=0;s<(1<<4);s++){
				f[i][j][s]=f[i-1][j][s^a[i]];
				ckmin(g[i][j],f[i][j][s]+s);
			}
			ckmin(f[i][j][a[i]],g[i-1][j-1]);
		}
	}
	for(int i=k;i<=n;i++) printf("%d ",g[i][k]);
}
