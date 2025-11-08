#include<bits/stdc++.h>
const int N=5e3+10,MOD=998244353;
int fac[N+1],ifac[N+1];
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int binom(int n,int k){
	return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int a[N],b[N],la[N],lb[N],lsa[N],lsb[N];
char c[N];
int main(){
	fac[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);
	for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
	int n;scanf("%d",&n);
	int cnt0=0;
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=n;j++){
			int t=c[j]=='1'?1:-1;
			a[i]+=t,b[j]+=t,
			cnt0+=c[j]=='0';
		}
	}
	std::sort(a+1,a+n+1,std::greater<int>());
	std::sort(b+1,b+n+1,std::greater<int>());
	for(int i=2,las=1;i<=n+1;i++){
		if(i==n+1||a[i]!=a[i-1]){
			for(int j=las;j<i;j++) la[j]=i-las,lsa[j]=las;
			las=i;
		}
	}
	for(int i=2,las=1;i<=n+1;i++){
		if(i==n+1||b[i]!=b[i-1]){
			for(int j=las;j<i;j++) lb[j]=i-las,lsb[j]=las;
			las=i;
		}
	}
	int ans=0;
	lsa[0]=lsb[0]=1;
	for(int s1=cnt0,x=0;x<=n;x++){
		s1+=a[x];
		for(int s2=cnt0,y=0;y<=n;y++){
			s2+=b[y];
			if(s1+s2==n*n+x*y+(n-x)*(n-y))
				ans=(ans+1ll*binom(la[x],x-lsa[x]+1)*binom(lb[y],y-lsb[y]+1))%MOD;
		}
	}
	printf("%d",ans);
}
