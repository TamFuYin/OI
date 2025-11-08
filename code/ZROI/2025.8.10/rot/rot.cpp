#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int N=5e3+10,MOD=998244353;
int a[N],b[N];
int stir2[N][N];
//int k=0;
//void make(int ai){
//	int i=1;
//	while(b[i]!=ai) ++i;
//	if(i==1) return;
//	int tmp=b[i];
//	for(int j=i;j>1;j--) b[j]=b[j-1];
//	b[1]=tmp;
//	++k;
//}
int main(){
	freopen("rot.in","r",stdin);
	freopen("rot.out","w",stdout);
	for(int i=0;i<N;i++){
		stir2[i][0]=i==0;
		for(int j=1;j<=i;j++)
			stir2[i][j]=(stir2[i-1][j-1]+1ll*j*stir2[i-1][j])%MOD;
//		for(int j=0;j<=i;j++)
//			printf("%d ",stir2[i][j]);
//		puts("");
	}
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	std::iota(b+1,b+n+1,1);
	int d=a[n],k=n-1;
	for(int i=n-1;i>=1;i--){
		if(a[i]>a[i+1]) break;
		--k;
	}
//	printf("%d\n",k);
	int ans=0;
	for(int i=k;i<=m;i++) (ans+=stir2[m][i])%=MOD;
	printf("%d\n",ans);
}
