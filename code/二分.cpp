#include<bits/stdc++.h>
const int N=1e3+10;
int mx[N],f[N][N];
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
int a[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	mx[0]=1e9;
	memset(f,0x3f,sizeof f);
	f[1][0]=a[1];mx[1]=a[1];
	for(int i=2;i<=n;i++){
		mx[i]=std::max(mx[i-1],a[i]);
		for(int x=0;x<=n;x++){
			if(a[i]<x) ckmin(f[i][x],f[i-1][x]+x);
			else if(a[i]<mx[i-1])
				ckmin(f[i][a[i]],f[i-1][x]+a[i]),
				ckmin(f[i][x],f[i-1][x]+mx[i-1]);
			else ckmin(f[i][x],f[i-1][x]+a[i]);
			// if(f[i][x]<1e9)
			// printf("f[%d,%d]=%d\n",i,x,f[i][x]);
		}
	}
	int ans=INT_MAX;
	for(int i=0;i<=n;i++) ckmin(ans,f[n][i]);
	printf("%d",ans);
}