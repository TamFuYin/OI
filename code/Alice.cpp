#include"Alice.h"
#include<bits/stdc++.h>
using ll=long long;
using pii=std::pair<int,int>;
using vpii=std::vector<pii>;
vpii Alice(){
	int n=5e3;ll x=setN(n);
	vpii ret;
	for(int i=2;i<=n;i++) ret.emplace_back(x%(i-1)+1,i);
	return ret;
}

