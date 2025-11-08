#include<bits/stdc++.h>
const int N=71,V=801;
int pre[N][N][N*V],suf[N][N][N*V];
int a[N];
int main(){
	int n,v;scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	std::sort(a+1,a+n+1);
	pre[0][0]=1;
	for(int i=1;i<=n;i++){
		memcpy(pre[i],pre[i-1],sizeof pre[0]);
		for(int j=a[i];j<=i*v;j++)
			(pre[i][j]+=pre[i-1][j-a[i]])%=MOD;
	}
	suf[n+1][0]=1;
	for(int i=n;i>=1;i--){
		memcpy(suf[i],suf[i+1],sizeof suf[0]);
		for(int j=a[i];j<=i*v;j++)
			(suf[i][j]+=suf[i+1][j-a[i]])%=MOD;
	}
	for(int i=1;i<=n;i++){
		
	}
}