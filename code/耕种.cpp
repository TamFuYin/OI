#include<bits/stdc++.h>
const int N=1e7;
using ll=long long;
ll s[N],mx[N];
int main(){
	freopen("farming.in","r",stdin);
	freopen("farming.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1,a;i<=n;i++)
		scanf("%d",&a),
		s[i]=s[i-1]+a,
		mx[i]=std::max(mx[i-1],s[i]);
	if(s[n]<0){
		puts("-1");
		return 0;
	}
	ll cur=0,d=n;
	for(int i=1;i<=n;i++){
		if(cur+s[i]<0){
			if(mx[i-1]<=0){
				puts("-1");
				return 0;
			}
			ll t=ceil(1.*(-(cur+s[i]))/mx[i-1]);
			d+=t,cur+=t*mx[i-1];
		}
		cur+=s[i];
	}
	printf("%lld",d);
}