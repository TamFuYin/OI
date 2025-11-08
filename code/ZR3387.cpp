#include<bits/stdc++.h>
template<typename T>
inline void ckmin(T &a,T b){if(b<a)a=b;}
const int N=1e5;
int a[N],b[N],la[N],ra[N],lb[N],rb[N];
int n;
struct queryData{
	int l,r,k,id;
};
std::vector<queryData> qd[N<<2];
int ans[N];
//线段猫树状分治
void CatSegDC(int L,int R,const queryData& k,int l=1,int r=n,int o=1){
	if(r-l+1<k.k) return;
	if(L<=l&&r<=R){
		qd[o].push_back(k);
		return;
	}
	int mid=l+r>>1;
	if(L<=mid&&mid<R) qd[o].push_back(k);
	if(L<=mid) CatSegDC(L,R,k,l,mid,o<<1);
	if(mid<R) CatSegDC(L,R,k,mid+1,r,o<<1|1);
}
struct optData{
	int x,v;
};
std::vector<optData> opts[N];
void solve(int l=1,int r=n,int o=1){
	if(l==r){
		for(auto q:qd[o]) ckmin(ans[q.id],std::abs(a[l]-b[l]));
		return;
	}
	int mid=l+r>>1;
	solve(l,mid,o<<1);
	solve(mid+1,r,o<<1|1);
	la[mid+1]=lb[mid+1]=INT_MAX;
	for(int i=mid;i>=l;i--) la[i]=std::min(la[i+1],a[i]),lb[i]=std::min(lb[i+1],b[i]);
	ra[mid]=rb[mid]=INT_MAX;
	for(int i=mid+1;i<=r;i++) ra[i]=std::min(ra[i-1],a[i]),rb[i]=std::min(rb[i-1],b[i]);
	for(int i=mid+1;i<=r;i++){
		int ap=std::lower_bound(la+l,la+mid+1,ra[i])-la,
		bp=std::lower_bound(lb+l,lb+mid+1,rb[i])-lb;
		opts[1].push_back({i,std::abs(la[l]-lb[l])});
	}
}
int main(){
    int c,q;scanf("%d%d%d",&c,&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
	std::fill(ans+1,ans+q+1,INT_MAX);
    for(int i=1;i<=q;i++){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
		CatSegDC(l,r,{l,r,k,i});
    }
	solve();
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}