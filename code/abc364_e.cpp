#include<bits/stdc++.h>
const int N=100,X=1.1e4;
int a[N],b[N],f[N][N][X];
int main(){
	int n,x,y;scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	memset(f,0x3f,sizeof f);
	f[0][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<a[i];k++) f[i][j][k]=f[i-1][j][k];
			if(j) for(int k=a[i];k<=x;k++){
				f[i][j][k]=std::min(f[i-1][j][k],f[i-1][j-1][k-a[i]]+b[i]);
			}
		}
	}
	for(int i=n;i>=0;i--) for(int j=0;j<=x;j++) if(f[n][i][j]<=y) {printf("%d",std::min(i+1,n));return 0;}
}
