#include<bits/stdc++.h>
#include"Alice.h"
#include"Bob.h"
using ll=long long;
std::mt19937_64 rnd(time(0));
ll X=rnd()%ll(1e18)+1;
//ll X=4005;
ll setN(int n){
	return X;
}
using pii=std::pair<int,int>;
using vpii=std::vector<pii>;
vpii v;
int main(){
	v=Alice();
	int n=v.size()+1;
	std::vector<int> a(n-1);
	std::iota(a.begin(),a.end(),0);
	std::shuffle(a.begin(),a.end(),rnd);
	for(int i=0;i<(n-2)/2;i++) v.erase(v.begin()+a[i]);
	assert(Bob(v)==X);fprintf(stderr,"Succeeded X=%lld",X);
}
