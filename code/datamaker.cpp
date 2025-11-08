#include<bits/stdc++.h>
std::mt19937_64 rnd(time(0));
using ll=long long;
const int N=1e5;
ll a[N*2];
int main(){
	freopen("data.txt","w",stdout);
	int T=10;
	printf("%d\n",T);
	while(T--){
		ll V=1e18+1;
		int n=1000;
		for(int i=0;i<3*n;i++) a[i]=rnd()%V;
		std::sort(a,a+3*n);
		std::unique(a,a+3*n);
		printf("%d\n",n);
		for(int i=1;i<=n;i++) printf("%lld %lld\n",a[i*2-1],a[i*2]);
	}
}
