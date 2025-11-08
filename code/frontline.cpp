#pragma GCC optimize(3)
#include<bits/stdc++.h>
const int N=5e5+10;
std::pair<int,int> a[N*2];
std::vector<int> _b[N*2],*b=_b+N;
#define sgn(x) ((x)>0?1:((x)<0?-1:0))
template<typename T>
T swap(T x){
	std::swap(x.first,x.second);
	return x;
}
using ll=long long;
std::vector<ll> c;
std::set<std::pair<ll,ll> > S/*antiODT*/,ODT;
void solve(std::vector<int>& b){
	int n=b.size()-1;
	assert(S.empty());
	assert(b.size()%2==0);
	for(int i=1;i<=n;i++)
		S.emplace(b[i]-b[i-1],i),
		ODT.emplace(i,b[i]-b[i-1]);
	while(!S.empty()){
		ll v=S.begin()->first,x=S.begin()->second;S.erase(S.begin());
		c.push_back(v);
		auto it=ODT.find({x,v});
		bool norm=1;
		v=-v;
		if(it!=ODT.begin()){
			auto pit=std::prev(it);
			x=pit->first;
			v+=pit->second;
			S.erase(swap(*pit));
			ODT.erase(pit);
		}
		else norm=0;
		auto nit=std::next(it);
		if(nit!=ODT.end()){
			v+=nit->second;
			S.erase(swap(*nit));
			ODT.erase(nit);
		}
		else norm=0;
		ODT.erase(it);
		if(norm){
			ODT.emplace(x,v);
			S.emplace(v,x);
		}
	}
}
int main(){
//	freopen("frontline4.in","r",stdin);
//	freopen("frontline4.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].first),a[i].second=1;
	for(int i=1;i<=n;i++) scanf("%d",&a[n+i].first),a[n+i].second=-1;
	int top=0;
	std::sort(a+1,a+n*2+1);
	for(int i=1;i<=n*2;i++){
		b[std::min(top,top+a[i].second)].push_back(a[i].first);
		top+=a[i].second;
	}
	for(int i=-n;i<=n;i++) if(!b[i].empty()) solve(b[i]);
	std::sort(c.begin(),c.end());
	ll ans=0;for(int i=0;i<n;i++) ans+=c[i],printf("%lld ",ans);
}
