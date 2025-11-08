//你就是我的 Xor Master 吗？
#include<bits/stdc++.h>
const int lgV=64;
using ull=unsigned long long;
struct LinearSpace{
	ull a[lgV];
	int insert(ull x){
		for(int i=lgV-1;~i;i--)
			if(x>>i&1){
				if(a[i]) x^=a[i];
				else{
					a[i]=x;
					for(int j=lgV-1;j>i;j--)
						if(a[j]>>i&1) a[j]^=x;
					return i;
				}
			}
		return -1;
	}
	ull min(ull x){
		for(int i=0;i<lgV;i++) if(a[i]&&(x>>i&1)) x^=a[i];
		return x;
	}
	ull max(ull x){
		for(int i=0;i<lgV;i++) if(a[i]&&!(x>>i&1)) x^=a[i];
		return x;
	}
}S;
const int N=1e5;
int n;
int lowbit(int x){
	return x&-x;
}
struct BIT{
	ull t[N];
	void add(int x,ull v){
		while(x<=n){
			t[x]^=v;
			x+=lowbit(x);
		}
	}
	ull operator[](int x)const{
		ull ret=0;
		while(x){
			ret^=t[x];
			x-=lowbit(x);
		}
		return ret;
	}
}s;
struct data{
	int a[lgV],len;
	data operator+(const data& b)const{
		static data ret;ret.len=len+b.len;
		for(int i=0;i<lgV;i++) ret.a[i]=a[i]+b.a[i];
		return ret;
	}
	void operator^=(const ull x){
		for(int i=0;i<lgV;i++) if(x>>i&1) a[i]=len-a[i];
	}
	void operator=(const ull x){
		len=1;
		for(int i=0;i<lgV;i++) a[i]=x>>i&1;
	}
	ull sum(){
		ull ret=0;
		for(int i=0;i<lgV;i++) ret+=a[i]<<i;
		return ret;
	}
}t[N*4];
ull tag[N*4];
void pushup(int o){
	t[o]=t[o<<1]+t[o<<1|1];
}
void pushtag(int o,int x){
	tag[o]^=x;t[o]^=x;
}
void pushdown(int o){
	if(tag[o]){
		pushtag(o<<1,tag[o]);
		pushtag(o<<1|1,tag[o]);
		tag[o]=0;
	}
}
void build(int l=1,int r=n,int o=1){
	if(l==r) return t[o]=S.max(s[l]);
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void modify(int L,int R,ull x,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return pushtag(o,x);
	int mid=l+r>>1;
	pushdown(o);
	if(L<=mid) modify(L,R,x,l,mid,o<<1);
	if(mid<R) modify(L,R,x,mid+1,r,o<<1|1);
	pushup(o);
}
ull query(int L,int R,int l=1,int r=n,int o=1){
	if(L>r||R<l) return 0;
	if(L<=l&&r<=R) return t[o].sum();
	int mid=l+r>>1;ull ret=0;
	pushdown(o);
	if(L<=mid) ret+=query(L,R,l,mid,o<<1);
	if(mid<R) ret+=query(L,R,mid+1,r,o<<1|1);
	return ret;
}
ull a[N];
int main(){
	int Q;scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%llu",a+i),s.add(i,a[i]);
	build();
	while(Q--){
		int opt,l,r,x;ull v;scanf("%d",&opt);
		switch(opt){
		case 1:
			scanf("%d%llu",&x,&v);
			s.add(x,v^a[x]);a[x]=v;
			modify(x,n,S.min(v));
			break;
		case 2:
			scanf("%llu",&v);
			if(~S.insert(v)) build();
			break;
		default:
			scanf("%d%d",&l,&r);
			v=S.min(s[l-1]);
			modify(l,r,v);
			printf("%llu\n",query(l,r));
			modify(l,r,v);
			break;
		}
	}
}
