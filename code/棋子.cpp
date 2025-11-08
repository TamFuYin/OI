#include<bits/stdc++.h>
const int MOD=1e9+7;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int main(){
	freopen("cp.in","r",stdin);
	freopen("cp.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		printf("%d\n",(qpow(n,MOD-2)+n-1)%MOD);
	}
}