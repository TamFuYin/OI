#include"lottery.h"
#include<bits/stdc++.h>
const int MAXN=2e5+10;
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
using ll=long long;
struct Discrete{
	int dsc[MAXN],n;
	void make(std::vector<int> a){
		n=a.size();
		std::copy(a.begin(),a.end(),dsc);
		std::sort(dsc,dsc+n);
		n=std::unique(dsc,dsc+n)-dsc;
	}
	int rnk(int k){
		return std::upper_bound(dsc,dsc+n,k)-dsc-1;
	}
}x,y;
int N;
struct data{
	ll sum;
	int siz;
	data operator+(const data& b)const{
		return {sum+b.sum,siz+b.siz};
	}
	data& operator+=(const data& b){
		(*this)=(*this)+b;
		return *this;
	}
};
struct HJT{
	struct node{
		data v;
		int ls,rs;
	}t[MAXN*20];int size;
	int rt[MAXN];
	#define mid ((l+r)>>1)
	void pushup(int p){
		t[p].v=t[t[p].ls].v+t[t[p].rs].v;
	}
	void insert(int& p,int x,int v,int l=0,int r=N-1){
		t[++size]=t[p];p=size;
		if(l==r){
			assert(!t[p].v.siz);
			t[p].v={v,1};
			return;
		}
		if(x<=mid) insert(t[p].ls,x,v,l,mid);
		else insert(t[p].rs,x,v,mid+1,r);
		pushup(p);
	}
	data query(int p,int L,int R,int l=0,int r=N-1){
		if(!p||L<=l&&r<=R) return t[p].v;
		if(L<=mid&&mid<R) return query(t[p].ls,L,R,l,mid)+query(t[p].rs,L,R,mid+1,r);
		if(L<=mid) return query(t[p].ls,L,R,l,mid);
		if(mid<R) return query(t[p].rs,L,R,mid+1,r);
	}
	#undef mid
}tx,ty;
std::pair<int,int> px[MAXN],py[MAXN];
int mn[MAXN][std::__lg(MAXN)+2];
int getMin(int l,int r){
	int k=std::__lg(r-l+1);
	return std::min(mn[l][k],mn[r-(1<<k)+1][k]);
}
void makeST(){
	for(int j=1;(1<<j)<=N;j++)
		for(int i=0;i+(1<<j)-1<N;i++)
			mn[i][j]=std::min(mn[i][j-1],mn[i+(1<<j-1)][j-1]);
}
void init(int _N,int Q,std::vector<int> X,std::vector<int> Y){
	N=_N;
	x.make(X),y.make(Y);
	// printf("x.n=%d\n",x.n);
	for(int i=0;i<N;i++) px[i]={X[i],i},py[i]={Y[i],i};
	std::sort(px,px+N);std::sort(py,py+N);
	for(int i=0,xcur=0,ycur=0;i<N;i++){
		// printf("x.rnk(%d)=%d\n",px[i].first,x.rnk(px[i].first));
		tx.insert(xcur,px[i].second,px[i].first),
		ty.insert(ycur,py[i].second,py[i].first);
		tx.rt[x.rnk(px[i].first)]=xcur,
		ty.rt[y.rnk(py[i].first)]=ycur;
	}
	for(int i=0;i<N;i++) mn[i][0]=X[i]+Y[i];
	makeST();
}
bool check(int L,int R,int K){
	data dx=tx.query(tx.rt[x.rnk(K)],L,R),dy=ty.query(ty.rt[y.rnk(K)],L,R);
	int l=R-L+1;ll lim=(ll)l*K/2;
	// printf("K=%d(%d) %d %d\n",K,x.rnk(K),dx.sum,dx.siz);
	return dx.sum+(ll)(l-dx.siz)*K>=lim&&dy.sum+(ll)(l-dy.siz)*K>=lim;
}
int max_prize(int L,int R){
	int len=R-L+1;
	return std::min(std::min(),getMin(L,R));
}