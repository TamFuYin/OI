#include<bits/stdc++.h>
int qpow(int a,int b,int MOD){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int cnt[10];int phi=0,k=INT_MAX;
using ll=long long;
void sort(__int128 n){
//	printf("%lld%lld:\t",ll(n/ll(1e9)),ll(n%ll(1e9)));
	memset(cnt,0,sizeof cnt);
	for(int i=1;i<=k;i++){
		++cnt[n%10];
		n/=10;
	}
	for(int i=0;i<=9;i++) printf("%d ",cnt[i]);
	puts("");
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<n;i++) if(std::__gcd(n,i)==1) ++phi;
	for(int i=1;i*i<=phi;i++){
		if(phi%i==0){
			if(qpow(10,i,n)==1) {k=i;break;}
		}
	}
	if(k==INT_MAX){
		for(int i=sqrt(phi-1);i>=1;i--){
			if(phi%i==0){
				if(qpow(10,phi/i,n)==1) {k=phi/i;break;}
			}
		}
	}
	__int128 p=((__int128)pow(10,k)-1)/n;
	for(int i=1;i<n;i++) printf("%2d:",i),sort(i*p);
}
