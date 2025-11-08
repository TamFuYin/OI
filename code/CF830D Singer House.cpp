#include<bits/stdc++.h>
const int N=4e2+10,MOD=1e9+7;
int f[N][N];
int main(){
	int n;scanf("%d",&n);
	f[1][0]=f[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;j+k<=n;k++){
				int tmp=1ll*f[i-1][j]*f[i-1][k]%MOD;
				(f[i][j+k-1]+=1ll*(j+k)*(j+k-1)%MOD*tmp%MOD)%=MOD;
				(f[i][j+k]+=1ll*(2*(j+k)+1)*tmp%MOD)%=MOD;
				(f[i][j+k+1]+=tmp)%=MOD;
			}
		}
	}
	printf("%d",f[n][1]);
}