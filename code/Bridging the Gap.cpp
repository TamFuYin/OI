#define ckmin(a,b) a=std::min(a,b)
#include<bits/stdc++.h>
const int N=1e3;
int f[N][N],t[N];
/*
f[i][j] 表示已经运走了 1~i，其中 1~j 又回来了
的最小时间
*/
int main(){
	int n,c;scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",t+i);
	std::sort(t+1,t+n+1);
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=j&&k<c;k++){
				if(i+c-k>=n) ckmin(f[n][j-k],f[i][j]+t[n]);
				else ckmin(f[i+c-k][j-k+1],f[i][j]+t[i+c-k]+t[j-k+1]);
			}
		}
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
		if(f[i][j]<1e9)
			printf("f[%d][%d]=%d\n",i,j,f[i][j]);
	for(int i=n;i>=1;i--){
		ckmin(f[n][i-std::min(i,c)],f[n][i]+t[i]);
	}
	printf("%d",f[n][0]);
}