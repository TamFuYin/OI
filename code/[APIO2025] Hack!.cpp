#include<bits/stdc++.h>
using ll=long long;
using vll=std::vector<ll>;
#define q collisions
const int m=1e5;
const ll V=1e18;
static ll a[m*2];
ll q(int l1,int r1,int l2,int r2){
	vll v(a+l1,a+r1);v.insert(v.end(),a+l2,a+r2);
	return q(v)-q({a+l1,a+r1})-q({a+l2,a+r2});
}
int hack(){
	std::mt19937_64 rnd(time(0));
	for(int i=0;i<m*2;i++) a[i]=rnd()%V+1;
	std::sort(a,a+m*2);
	std::unique(a,a+m*2);
	int l1=0,r1=m/2,l2=m/2,r2=m;
	while(l1<r1+1){
		if(q(l1,r1,l2,r2))
	}
}