#include<bits/stdc++.h>
using ll=long long;
void exgcd(ll a,ll& x,ll b,ll& y){
	if(b==0){
		x=1,y=0;
		return;
	}
	exgcd(b,y,a%b,x);
	y-=a/b*x;
}
ll inv(ll a,ll m){
	ll x,y;
	exgcd(a,x,m,y);
	return (x%m+m)%m;
}
ll qpow(ll a,ll b,ll m){
	ll c=1;
	while(b){
		if(b&1) c=(__int128)c*a%m;
		a=(__int128)a*a%m;b>>=1;
	}
	return c;
}
int main(){
	freopen("encrypt.in","r",stdin);
	freopen("encrypt.out","w",stdout);
	ll p,q,e;scanf("%lld%lld%lld",&p,&q,&e);
	ll N=p*q,r=(p-1)*(q-1),d=inv(e,r);
	int L;scanf("%d",&L);
	while(L--){
		ll c;scanf("%lld",&c);
		printf("%lld ",qpow(c,d,N));
	}
}