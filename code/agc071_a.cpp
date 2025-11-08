#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
using ll=long long;
const int N=1e2+10;
ll a[N],s[N],f[N][N][N];
ll dp(int l,int r,int k){
	if(k){
		for(int i=k+(k-l&1);i<r;i+=2) ckmin(ret,dp(l,i,k)+dp(i+1,r,0));
	}
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	ll ans=LLONG_MAX;
	if(n&1) for(int i=1;i<=n;i++) ckmin(ans,dp(1,n,i));
	else ans=dp(1,n,0);
	printf("%lld",ans);
}