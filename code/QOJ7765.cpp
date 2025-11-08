/*其实某种程度上挺板的*/
#include<bits/stdc++.h>
const int N=1e5;
using ll=unsigned long long;
ll s[N];int n;
int cnt[N*4][64];
void pushup(int o){
	for(int i=0;i<64;i++)
		cnt[o][i]=cnt[o<<1][i]+cnt[o<<1|1][i];
}
void build(int l=1,int r=n,int o=1){
	if(l==r){
		for(int i=0;i<64;i++) cnt[o][i]=s[l]>>i&1;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
ll b[64];
int h(ll v){
	for(int i=63;i>=0;i--){
		if(v>>i&b[i]>>i&1){
			v^=b[i];
		}
	}
}
void update(int L,int R,ll v,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R){
		for(int i=0;i<64;i++)
			if(v>>i&1) cnt[o][i]=r-l+1-cnt[o][i];
		return;
	}
	int mid=l+r>>1;
	if(L<=mid) update(L,R,v,l,mid,o<<1);
	if(mid<R) update(L,R,v,mid+1,r,o<<1|1);
	pushup(o);
}
bool insert(ll v){
	for(int i=63;i>=0;i--){
		if(v>>i&1){
			if(b[i]) v^=b[i];
			else return b[i]=v,true;
		}
	}
	return false;
}
int main(){
	int q;scanf("%d%d",&n,&q);
	for(int i=1,ai;i<=n;i++) scanf("%d",&ai),s[i]=s[i-1]^ai;
	build();
	while(q--){
		int opt;scanf("%d",&opt);
		switch(opt){
		case 1:
			int x;ll v;scanf("%d%lld",&x,&v);
			update(x,n,h(v));
			break;
		case 2:
			if(insert(x))
			break;
		default:
			//TODO
			break;
		}
	}
}
