#include<bits/stdc++.h>
using ll=long long;
struct data{
	int v;
	bool type;
	bool operator<(const data& b)const{
		return v>b.v||v==b.v&&type>b.type;
	}
};
std::priority_queue<data> Q;
const int N=1e5+10;
int a[N],b[N];
int n;
std::pair<int,ll> check(int k){
	while(!Q.empty()) Q.pop();
	ll ans=0;
	int flow=0;
	for(int i=1;i<=n;i++){
		Q.push({a[i]-k,1});
		if((ll)Q.top().v+b[i]<0){
			ans+=(ll)Q.top().v+b[i];
			flow+=Q.top().type;
			Q.pop();
			Q.push({-b[i],0});
		}
	}
	return {flow,ans};
}
int main(){
	freopen("world.in","r",stdin);
	freopen("world.out","w",stdout);
	int k;scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	int l=0,r=2e9;
	while(l<r){
		int mid=(ll)l+r+1>>1;
		if(check(mid).first<=k) l=mid;
		else r=mid-1;
	}
	auto p=check(l);
	printf("%lld",p.second+1ll*k*l);
}
