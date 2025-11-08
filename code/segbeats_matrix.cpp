#include<bits/stdc++.h>
const int N=5e5+10,INF=2e9;
int a[N];
using ll=long long;
struct vector{
	int a,b;vector(){}
	vector(const int& a,const int& b):a(a),b(b){}
	vector(const int k):a(k),b(k){}
	bool operator!=(const vector& _)const{
		return a!=_.a||b!=_.b;
	}
}I(0,-INF);
vector operator+(const vector& a,const vector& b){
	return vector(std::max(a.a,b.a),std::max(a.b,b.b));
}
vector operator*(const vector& a,const vector& b){
	return vector(b.a+a.a,std::max(b.a+a.b,b.b));
}
void operator*=(vector& a,const vector& b){a=b*a;}
struct node{
	vector mx,se;
	vector MX,SE;
	int len,mxcnt;ll sum;
	void plus_mx(const vector& k){
//		if(len==0) return;
		mx*=k,MX*=k,sum+=1ll*k.a*mxcnt;
	}
	void plus_se(const vector& k){
		if(se.a==-INF) return;
		se*=k,SE*=k,sum+=1ll*k.a*(len-mxcnt);
	}
	void plus(const vector& k){
		plus_mx(k),plus_se(k);
	}
}t[N*4];
void pushup(int o){
	t[o].sum=t[o<<1].sum+t[o<<1|1].sum;
	if(t[o<<1].mx.a==t[o<<1|1].mx.a){
		t[o].mxcnt=t[o<<1].mxcnt+t[o<<1|1].mxcnt;
		t[o].mx=t[o<<1].mx+t[o<<1|1].mx;
		t[o].se=t[o<<1].se+t[o<<1|1].se;
	}
	else{
		node a=t[o<<1],b=t[o<<1|1];
		if(a.mx.a<b.mx.a) std::swap(a,b);
		t[o].mxcnt=a.mxcnt;
		t[o].mx=a.mx;
		t[o].se=a.se+b.mx+b.se;
	}
}
void pushdown(int o){
	if(t[o<<1].mx.a==t[o<<1|1].mx.a){
		if(t[o].MX!=I){
			t[o<<1].plus_mx(t[o].MX);
			t[o<<1|1].plus_mx(t[o].MX);
			t[o].MX=I;
		}
		if(t[o].SE!=I){
			t[o<<1].plus_se(t[o].SE);
			t[o<<1|1].plus_se(t[o].SE);
			t[o].SE=I;
		}
	}
	else{
		bool b=t[o<<1].mx.a<t[o<<1|1].mx.a;
		if(t[o].MX!=I){
			t[o<<1|b].plus_mx(t[o].MX);
			t[o].MX=I;
		}
		if(t[o].SE!=I){
			t[o<<1|b].plus_se(t[o].SE);
			t[o<<1|!b].plus_mx(t[o].SE);
			t[o<<1|!b].plus_se(t[o].SE);
			t[o].SE=I;
		}
	}
}
void makemin(int o,int k){
	if(k>=t[o].mx.a) return;
	if(k>t[o].se.a){
		t[o].plus_mx(k-t[o].mx.a);
		return;
	}
	pushdown(o);
	makemin(o<<1,k);
	makemin(o<<1|1,k);
	pushup(o);
}
int n;
void plus(int L,int R,int k,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) {t[o].plus(k);return;}
	int mid=l+r>>1;pushdown(o);
	if(L<=mid) plus(L,R,k,l,mid,o<<1);
	if(mid<R) plus(L,R,k,mid+1,r,o<<1|1);
	pushup(o);
}
void makemin(int L,int R,int k,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) {makemin(o,k);return;}
	int mid=l+r>>1;pushdown(o);
	if(L<=mid) makemin(L,R,k,l,mid,o<<1);
	if(mid<R) makemin(L,R,k,mid+1,r,o<<1|1);
	pushup(o);
}
ll getsum(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o].sum;
	int mid=l+r>>1;ll ret=0;pushdown(o);
	if(L<=mid) ret+=getsum(L,R,l,mid,o<<1);
	if(mid<R) ret+=getsum(L,R,mid+1,r,o<<1|1);
	return ret;
}
int getmax(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o].mx.a;
	int mid=l+r>>1,ret=-INF;pushdown(o);
	if(L<=mid) ret=getmax(L,R,l,mid,o<<1);
	if(mid<R) ret=std::max(ret,getmax(L,R,mid+1,r,o<<1|1));
	return ret;
}
int gethmax(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return (t[o].mx+t[o].se).b;
	int mid=l+r>>1,ret=-INF;pushdown(o);
	if(L<=mid) ret=gethmax(L,R,l,mid,o<<1);
	if(mid<R) ret=std::max(ret,gethmax(L,R,mid+1,r,o<<1|1));
	return ret;
}
void build(int l=1,int r=n,int o=1){
	t[o].len=r-l+1;
	t[o].MX=t[o].SE=I;
	if(l==r){
		t[o].mx=a[l];
		t[o].se=-INF;
		t[o].sum=a[l];
		t[o].mxcnt=1;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
int main(){
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build();
	while(m--){
		int op,l,r,k;
		scanf("%d%d%d",&op,&l,&r);
		switch(op){
			case 1:scanf("%d",&k);plus(l,r,k);break;
			case 2:scanf("%d",&k);makemin(l,r,k);break;
			case 3:printf("%lld\n",getsum(l,r));break;
			case 4:printf("%d\n",getmax(l,r));break;
			case 5:printf("%d\n",gethmax(l,r));break;
		}
	}
}
