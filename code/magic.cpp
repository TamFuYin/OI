#include<bits/stdc++.h>
//#include"Alice.h"
//#include"Bob.h"
ll setN(int n);
using ll=long long;
using pii=std::pair<int,int>;
using vpii=std::vector<pii>;
vpii Alice(){
	int n=5e3;ll x=setN(n);
	vpii ret;
	for(int i=2;i<=n;i++) ret.emplace_back(x%(i-1)+1,i);
	return ret;
}
ll Bob(vpii v){
	ll mod=1,res=0;
	for(pii p:v){
		while(res%(p.second-1)+1!=p.first) res+=mod;
		mod=mod/std::__gcd(mod,ll(p.second-1))*(p.second-1);
	}
	return res;
}
