#include<bits/stdc++.h>
const int N=4e5+10;
struct line{
	double k,b;
	void fire(double x){b+=k*x;}
};
struct node{
	line mx;
	double melt,tag;
	void fire(double x){
		mx.fire(x);
		melt-=x;
	}
}t[N*4];
int n;
double cross(line u,line v){return u.k!=v.k&&(u.k<v.k^u.b<v.b)?(v.b-u.b)/(u.k-v.k):DBL_MAX;}
bool operator<(line u,line v){return u.b<v.b;}
line operator+(line u,line v){return {u.k+v.k,u.b+v.b};}
line combine(line u,line v,double& melt){
	melt=std::min(melt,cross(u,v));
	return std::max(u,v);
}
void pushup(int o){
	t[o].melt=std::min(t[o<<1].melt,t[o<<1|1].melt);
	t[o].mx=combine(t[o<<1].mx,t[o<<1|1].mx,t[o].melt);
}
void pushdown(int o){
	if(t[o].tag){
		t[o<<1].fire(t[o].tag),t[o<<1].tag+=t[o].tag;
		t[o<<1|1].fire(t[o].tag),t[o<<1|1].tag+=t[o].tag;
		t[o].tag=0;
	}
}
void build(int l=1,int r=n,int o=1){
	if(l==r){
		t[o].mx=line{1.0/l,0};
		t[o].tag=0;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void update(int l,int r,int o){
	if(l==r){
		t[o].mx=line{1.0/l,-t[o].melt/l};
		t[o].melt=LLONG_MAX;t[o].tag=0;
		return;
	}
	pushdown(o);
	int mid=l+r>>1;
	if(t[o<<1].melt<0) update(l,mid,o<<1);
	if(t[o<<1|1].melt<0) update(mid+1,r,o<<1|1);
	pushup(o);
}
void add(int L,int R,int x,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R){
		t[o].fire(x);
		t[o].tag+=x;
		if(t[o].melt<0) update(l,r,o);
		return;
	}
	int mid=l+r>>1;
	pushdown(o);
	if(L<=mid) add(L,R,x,l,mid,o<<1);
	if(mid<R) add(L,R,x,mid+1,r,o<<1|1);
	pushup(o);
}
int main(){
	scanf("%d",&n);build();
	for(int i=1;i<=n;i++){
		int ai;scanf("%d",&ai);
		add(ai,n,1);
		printf("%d ",(int)ceil(t[1].mx.b));
	}
}
