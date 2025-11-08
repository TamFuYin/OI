#include<bits/stdc++.h>
const int N=52;
using ll=long long;
ll f[N*N][N][N];
int a[N][N];
int main(){
	int h,w,k;
	scanf("%d%d%d",&h,&w,&k);
	memset(f,-0x7f,sizeof f);
	int si,sj;
	scanf("%d%d",&si,&sj);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			scanf("%d",&a[i][j]);
		}
	}
	f[0][si][sj]=0;
	for(int k=1;k<=h*w;k++){
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				f[k][i][j]=std::max(f[k-1][i][j],
				std::max(std::max(f[k-1][i-1][j],f[k-1][i][j-1]),
				std::max(f[k-1][i+1][j],f[k-1][i][j+1])))+a[i][j];
//				printf("%d ",f[k][i][j]);
			}
//			puts("");
		}
//		puts("");
	}
	ll ans=0;
	if(k<=h*w){
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				ans=std::max(ans,f[k][i][j]);
			}
		}
		printf("%lld",ans);
	}
	else{
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				ans=std::max(ans,f[h*w][i][j]+1ll*(k-h*w)*a[i][j]);
			}
		}
		printf("%lld",ans);
	}
}
