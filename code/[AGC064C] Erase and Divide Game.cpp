#include<bits/stdc++.h>
using ll=long long;
const int N=1e5;
struct seg{
	ll l,r;
	short sg;
}a[N],b[N];
short mex(short sg1,short sg2){
	if(sg1+sg2==-2) return -1;
	if(sg1+sg2==2) return 0;
	return 1;
}
int main(){
	freopen("data.txt","r",stdin);
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
			ll p=1ll<<k;int _m=0;
//			for(int i=1,j=1;i<=m&&a[i].l<p;i++){
//				while(j<=m&&a[i].l>a[j].r-p) ++j;
//				while(j<=m&&a[i].r>=a[j].l-p){
//					b[++_m]={std::max(a[i].l,a[j].l-p),
//					std::min(a[i].r,a[j].r-p),
//					mex(a[i].sg,a[j].sg)};
//					++j;
//				}
//				--j;
//			}
			for(int i=1;i<=m;i++){
				for(int j=1;j<=m;j++){
					ll l=std::max(a[i].l,a[j].l-p),
					r=std::min(a[i].r,a[j].r-p);
					if(l<=r) b[++_m]={l,r,mex(a[i].sg,a[j].sg)};
				}
			}
			m=0;
			for(int i=1;i<=_m;i++){
				if(i>1&&b[i].sg==b[i-1].sg) a[m].r=b[i].r;
				else a[++m]=b[i];
			}
//			for(int i=1;i<=m;i++) printf("[%lld,%lld] %hi\n",a[i].l,a[i].r,a[i].sg);
		}
		puts(a[1].sg?"Takahashi":"Aoki");
	}
}
