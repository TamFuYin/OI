#include<bits/stdc++.h>
using ll-long long;
const int P=1e9+7,INV2=(P+1)/2;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%P;
		a=1ll*a*a%P;b>>=1;
	}
	return ret;
}
std::pair<int,int> pair[N];
std::vector<std::tuple<int,int,int> > op;
#define pb push_back
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		bool flg1=1,flg2=1;
		for(int i=1;i<=n;i++){
			scanf("%d",b+i);
			if(b[i]!=b[1]) flg1=0;
			if(b[i]!=a[i]) flg2=0;
		}
		if(flg1){
			puts(flg2?"Yes\n0":"No");
			continue;
		}
		for(int i=1;i<=n;i++) pair[i]={b[i],a[i]};
		std::sort(pair+1,pair+n+1);
		for(int i=1;i<=n;i++) std::tie(b[i],a[i])=pair[i];
		for(int i=1;i<n;i++){
			if(a[i]!=1)
				op.pb(i,n,a[i]-1),
				a[n]=1ll*a[n]*(a[i]-1)%P;
			if(i!=1) op.pb(1,i,b[i]);
		}
		op.pb(1,n,qpow(a[n],P-2));
		op.pb(n,1,P);
		op.pb(1,n,2);
		if(b[1]!=1){
			if(b[1]==2){
			}
			else op.pb(n,1,b[1]);
		}
		
	}
}