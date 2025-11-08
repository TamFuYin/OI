#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int N=2e5+10;
int R[N],F[N];
int mu[N];
std::vector<int> pr;
bool npr[N];
const int MOD=998244353;
int qpow(int a,int b){
	b=(b+MOD-1)%(MOD-1);
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
const int I9=qpow(9,-1);
int et[N],t[N];
int ans[N];
int main(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!npr[i]) pr.push_back(i),mu[i]=-1;
		for(int j:pr){
			if(1ll*i*j>=N) break;
			npr[i*j]=1;
			if(i%j==0){
				mu[i*j]=0;
				break;
			}
			mu[i*j]=-mu[i];
		}
	}
	for(int i=1;i<N;i++) R[i]=1ll*(qpow(10,i)-1)*I9%MOD;
	for(int n=1;n<N;n++){
		F[n]=1;
		for(int d=1;d*d<=n;d++)
			if(n%d==0){
				F[n]=1ll*F[n]*qpow(R[n/d],mu[d])%MOD;
				if(d*d!=n)
					F[n]=1ll*F[n]*qpow(R[d],mu[n/d])%MOD;
			}
	}
	int n;scanf("%d",&n);
	std::fill(et,et+N,1e9);
	for(int i=1,ai;i<=n;i++)
		scanf("%d",&ai),ckmin(et[ai],i);
	for(int i=1;i<N;i++){
		t[i]=1e9;
		for(int j=1;i*j<N;j++)
			ckmin(t[i],et[i*j]);
	}
	std::fill(ans,ans+n+1,1);
	for(int i=1;i<N;i++)
		if(t[i]<=n) ans[t[i]]=1ll*ans[t[i]]*F[i]%MOD;
	for(int i=1;i<=n;i++){
		ans[i]=1ll*ans[i]*ans[i-1]%MOD;
		printf("%d\n",ans[i]);
	}
}
