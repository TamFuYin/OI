#include<bits/stdc++.h>
const int N=5e5+10,INF=2e9;
int a[N];
using ll=long long;
struct node{
	int max,hmax;ll sum;
	int mxcnt,sec,plus,plus_max,len,mmin;
}t[N*4];
void maketag_plus(int o,int k,int xk){
	t[o].plus_max=std::max(t[o].plus_max,t[o].plus+xk);
	t[o].hmax=std::max(t[o].hmax,t[o].max+xk);
	t[o].plus+=k,t[o].sum+=1ll*t[o].len*k,t[o].max+=k;
	if(t[o].sec!=-INF) t[o].sec+=k;
	if(t[o].mmin!=INF) t[o].mmin+=k;
}
void pushup(int o){
	t[o].max=std::max(t[o<<1].max,t[o<<1|1].max);
	t[o].sum=t[o<<1].sum+t[o<<1|1].sum;
	t[o].hmax=std::max(t[o<<1].hmax,t[o<<1|1].hmax);
	if(t[o<<1].max==t[o<<1|1].max){
		t[o].mxcnt=t[o<<1].mxcnt+t[o<<1|1].mxcnt;
		t[o].sec=std::max(t[o<<1].sec,t[o<<1|1].sec);
	}
	else{
		node a=t[o<<1],b=t[o<<1|1];
		if(a.max<b.max) std::swap(a,b);
		t[o].mxcnt=a.mxcnt;
		t[o].sec=std::max(a.sec,b.max);
	}
}
void pushdown(int);
void makemin(int o,int k){
	if(k>=t[o].max) return;
	if(k>t[o].sec){
		t[o].sum-=1ll*t[o].mxcnt*(t[o].max-k);
		t[o].max=k;t[o].mmin=std::min(t[o].mmin,k);
		return;
	}
	k=std::min(t[o].mmin,k);
	t[o].mmin=INF;
	pushdown(o);
	makemin(o<<1,k);
	makemin(o<<1|1,k);
	pushup(o);
}
void pushdown(int o){
	if(t[o].plus!=0||t[o].plus_max!=0){
		maketag_plus(o<<1,t[o].plus,t[o].plus_max);
		maketag_plus(o<<1|1,t[o].plus,t[o].plus_max);
		t[o].plus=t[o].plus_max=0;
	}
	if(t[o].mmin!=INF){
		makemin(o<<1,t[o].mmin);
		makemin(o<<1|1,t[o].mmin);
		t[o].mmin=INF;
	}
}
int n;
void plus(int L,int R,int k,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) {maketag_plus(o,k,std::max(k,0));return;}
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
	if(L<=l&&r<=R) return t[o].max;
	int mid=l+r>>1,ret=-INF;pushdown(o);
	if(L<=mid) ret=getmax(L,R,l,mid,o<<1);
	if(mid<R) ret=std::max(ret,getmax(L,R,mid+1,r,o<<1|1));
	return ret;
}
int gethmax(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o].hmax;
	int mid=l+r>>1,ret=-INF;pushdown(o);
	if(L<=mid) ret=gethmax(L,R,l,mid,o<<1);
	if(mid<R) ret=std::max(ret,gethmax(L,R,mid+1,r,o<<1|1));
	return ret;
}
void build(int l=1,int r=n,int o=1){
	t[o].len=r-l+1;
	t[o].mmin=INF;t[o].sec=-INF;
	t[o].plus=t[o].plus_max=0;
	if(l==r){
		t[o].sum=t[o].hmax=t[o].max=a[l];t[o].mxcnt=1;
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
