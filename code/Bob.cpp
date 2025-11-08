#include<bits/stdc++.h>
#include"Bob.h"
using ll=long long;
using pii=std::pair<int,int>;
using vpii=std::vector<pii>;
ll Bob(vpii v){
	ll mod=1,res=0;
	for(pii p:v){
		while(res%(p.second-1)+1!=p.first) res+=mod;
		mod=mod/std::__gcd(mod,ll(p.second-1))*(p.second-1);
	}
	return res;
}
