#include<bits/stdc++.h>
using ll=long long;
int main(){
	ll n;scanf("%lld",&n);
	ll ans=LLONG_MAX;
	for(ll x=0;x<=1e6;x++){
		int l=0,r=1e6;
		while(l<r){
			int mid=l+r>>1;
			if((x+mid)*(x*x+(ll)mid*mid)>=n) r=mid;
			else l=mid+1;
		}
		ans=std::min(ans,(x+l)*(x*x+(ll)l*l));
	}
	printf("%lld",ans);
}