#include<bits/stdc++.h>
const int MOD=998244353,N2=(MOD+1)/2,N=2e5+10;
int p2[N],suf[N],s3[N];
int tmp[N*2],*pow2=tmp+N;
int a[N];
int main(){
	pow2[0]=1;
	for(int i=1;i<N;i++) pow2[i]=pow2[i-1]*2%MOD;
	for(int i=-1;i>-N;i--) pow2[i]=1ll*pow2[i+1]*N2%MOD;
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d",a+i),p2[i]=p2[i-1]+(a[i]==2);
		suf[n+1]=0;
		for(int i=n;i>=1;i--)
			if(a[i]==3) suf[i]=(suf[i+1]+pow2[p2[i]])%MOD;
			else suf[i]=suf[i+1];
		for(int i=1;i<=n;i++) if(a[i]==1)
			(ans+=1ll*suf[i+1]*pow2[-p2[i]]%MOD)%=MOD;
		s3[n+1]=0;
		for(int i=n;i>=1;i--) s3[i]=s3[i+1]+(a[i]==3);
		for(int i=1;i<=n;i++) if(a[i]==1) (ans+=MOD-s3[i])%=MOD;
		printf("%d\n",ans);
	}
}