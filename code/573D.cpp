#include<bits/stdc++.h>
using ll=long long;
const int N=1e5;
int w[N],h[N];
int pw[N],ph[N];
int rw[N],rh[N];
int ban[N];
template<typename _T>
void mmax(_T& a,_T b){a=std::max(a,b);}
const ll INF=1e18;
struct vector{
	ll a[3];
	vector(ll x=-INF){std::fill(a+1,a+3,-INF);a[0]=x;}
};
struct matrix{
	ll a[3][3];
	matrix(){std::fill(a[0],a[0]+9,-INF);}
	matrix(std::initializer_list<ll> _a){std::copy(_a.begin(),_a.end(),a[0]);}
	matrix operator*(const matrix& b)const{
		matrix c;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					mmax(c.a[i][j],a[i][k]+b.a[k][j]);
		return c;
	}
	vector operator*(const vector& b)const{
		vector c;
		for(int i=0;i<3;i++)
			for(int k=0;k<3;k++)
				mmax(c.a[i],a[i][k]+b.a[k]);
		return c;
	}
}t[N*4];
int n;
matrix make_trans(int i){
	ll v3=-INF,v2=-INF,v1=-INF;
	if(ban[i]!=i) v1=(ll)w[i]*h[i];
	if(i>1&&ban[i-1]!=i&&ban[i]!=i-1) v2=(ll)w[i-1]*h[i]+(ll)w[i]*h[i-1];
	if(i>2&&ban[i-2]!=i-1&&ban[i-1]!=i&&ban[i]!=i-2) v3=(ll)w[i-2]*h[i-1]+(ll)w[i-1]*h[i]+(ll)w[i]*h[i-2];
	if(i>2&&ban[i-1]!=i-2&&ban[i]!=i-1&&ban[i-2]!=i) mmax(v3,(ll)w[i-1]*h[i-2]+(ll)w[i]*h[i-1]+(ll)w[i-2]*h[i]);
	return {v1,v2,v3,0,-INF,-INF,-INF,0,-INF};
}
void pushup(int o){t[o]=t[o<<1|1]*t[o<<1];}
void build(int l=1,int r=n,int o=1){
	if(l==r) return t[o]=make_trans(l),void();
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void update(int x,int l=1,int r=n,int o=1){
	if(x>r) return;
	if(l==r) return t[o]=make_trans(l),void();
	int mid=l+r>>1;
	if(x<=mid) update(x,l,mid,o<<1);
	else update(x,mid+1,r,o<<1|1);
	pushup(o);
}
int main(){
	int q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	for(int i=1;i<=n;i++) scanf("%d",h+i);
	std::iota(pw+1,pw+n+1,1);std::iota(ph+1,ph+n+1,1);
	std::sort(pw+1,pw+n+1,[](const int& a,const int& b){return w[a]<w[b];});
	std::sort(ph+1,ph+n+1,[](const int& a,const int& b){return h[a]<h[b];});
	for(int i=1;i<=n;i++) rw[pw[i]]=rh[ph[i]]=i;
	for(int i=1;i<=n;i++) ban[rw[i]]=rh[i];
	std::sort(w+1,w+n+1),std::sort(h+1,h+n+1);
	build();
	while(q--){
		int a,b;scanf("%d%d",&a,&b);
		std::swap(ban[rw[a]],ban[rw[b]]);
		update(rw[a]);update(rw[a]+1);update(rw[a]+2);
		update(rw[b]);update(rw[b]+1);update(rw[b]+2);
		printf("%lld\n",(t[1]*0).a[0]);
	}
}
