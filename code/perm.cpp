// #include "perm.h"
#include<bits/stdc++.h>
using vi=std::vector<int>;
using ll=long long;
vi solve(ll k){
	--k;
	vi a,v;int n=0;
	for(int i=std::__lg(k+1);i;i--)
		while((1ll<<i)-1<=k){
			v.clear();
			for(int j=n;j<n+i;j++) v.push_back(j);
			a.insert(a.begin(),v.begin(),v.end());
			n+=i,k-=(1ll<<i)-1;
		}
	return a;
}
vi construct_permutation(ll k){
	n=0;
	vi a;
	while(k!=1){
		ll p=PollardRho(k);
	}
	return a;
}