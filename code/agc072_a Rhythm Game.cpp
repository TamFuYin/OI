#include<bits/stdc++.h>
const int N=1e5;
using ll=long long;
struct data{
	ll t,x;
	bool operator<(const data& b)const{
		return t<b.t||t==b.t&&x<b.x;
	}
}a[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;ll d;scanf("%d%lld",&n,&d);
		ll cur=0;bool no=0;
		for(int i=1;i<=n;i++)
			scanf("%lld%lld",&a[i].t,&a[i].x);
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			cur+=a[i].x;
			if(cur<a[i].t) cur+=(a[i].t-cur+1)/2*2;
			// printf(">> %d\n",cur);
			if(!(cur<=a[i].t+d)) no=1;
			cur+=a[i].x;
		}
		puts(no?"No":"Yes");
	}
}