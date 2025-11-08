#include<bits/stdc++.h>
using ll=long long;
const int N=1e6;
struct seg{
	ll l,r;
	int sg;
	seg operator+(const seg& b)const{
		return {std::max(l,b.l),std::min(r,b.r),sg+b.sg==-2?-1:sg+b.sg!=2};
	}
}a[N],b[N];
std::vector<seg> L,R;
int main(){
	freopen("data.txt","r",stdin);
	freopen("pai.txt","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		ll las=-1;
		int m=0;
		while(n--){
			ll l,r;scanf("%lld%lld",&l,&r);
			if(las+1!=l) a[++m]={las+1,l-1,-1};
			a[++m]={l,r,0};
			las=r;
		}
		if(las!=(1ll<<60)-1) a[++m]={las+1,(1ll<<60)-1,-1};
		for(int k=59;k>=0;k--){
			ll p=1ll<<k;
			L.clear();R.clear();
			for(int i=1;i<=m;i++){
				if(a[i].l<p) L.push_back({a[i].l,std::min(a[i].l,p-1),a[i].sg});
				if(a[i].r>=p) R.push_back({std::max(a[i].l,p)-p,a[i].r-p,a[i].sg});
			}
			m=0;
			for(auto i=L.begin(),j=R.begin();i!=L.end()&&j!=R.end();){
				ll x=std::min(i->r,j->r);
				a[++m]=*i+*j;
				if(i->r==x) ++i;
				if(j->r==x) ++j;
			}
		}
		puts(a[1].sg?"Takahashi":"Aoki");
	}
}
