/*
#include<bits/stdc++.h>
int main(){
freopen("input.txt","w",stdout);
int n=1e5;
printf("%d %d\n",n,n);
std::mt19937 rd(time(0));
for(int i=1;i<=n;i++) printf("%d ",rd()%int(1e9));
puts("");
for(int i=1;i<=n;i++){
int t=rd()%2+1,l=(rd()-1)%n+1,r=rd()%(n-l+1)+l;
printf("%d %d %d ",t,l,r);
if(t==1) printf("%d",rd()%int(1e9));
puts("");
}
}
*/
#include<bits/stdc++.h>
using ll=long long;
const int N=1e5+10,B=sqrt(N)+5,LB=log2(B)+5;
struct vector{ll x,y;
	void plusf(ll k){y+=k*x;}
	ll cut(ll k){return y-k*x;}
	double k(){return 1.*y/x;}
};
vector operator+(const vector& a,const vector& b){return {a.x+b.x,a.y+b.y};}
vector operator-(const vector& a,const vector& b){return {a.x-b.x,a.y-b.y};}
ll operator*(const vector& a,const vector& b){return a.x*b.y-a.y*b.x;}
vector memory[N];vector *cur=memory;
vector* alloc(int size){
	vector* tmp=cur;
	cur+=size;
	return tmp;
}
void free(int size){
	cur-=size;
}
void clear(){
	cur=memory;
}
struct hull{
	vector* p;int len;
	vector vec(int i){
		if(i==1) return p[i];
		else return p[i]-p[i-1];
	}
	void print()const{
		for(int i=1;i<=len;i++) printf("(%lld,%lld) ",p[i].x,p[i].y);
		puts("");
	}
	friend hull operator+(hull a,hull b){//闵可夫斯基和
		int len=0;vector *c=alloc(B*2+1);c[0]={0,0};
		for(int i=1,j=1;i<=a.len||j<=b.len;++len){
			if(j>b.len) c[len+1]=c[len]+a.vec(i++);
			else if(i>a.len) c[len+1]=c[len]+b.vec(j++);
			else if(b.vec(i)*a.vec(i)>0) c[len+1]=c[len]+a.vec(i++);
			else c[len+1]=c[len]+b.vec(j++);
		}
		return {c,len};
	}
	friend hull operator+(hull a,vector b){
		vector *c=alloc(B*2+1);c[1]=b;
		for(int i=1;i<=a.len;i++) c[i+1]=a.p[i]+b;
		int len=1;
		for(int i=2;i<=a.len+1;i++){
			while(len>1&&(c[len]-c[len-1])*(c[i]-c[len])>0) --len;
			c[++len]=c[i];
		}
		return {c,len};
	}
	void plusf(int k){
		for(int i=1;i<=len;i++) p[i].plusf(k);
	}
	hull operator=(hull a){
		len=a.len;
		std::copy(a.p+1,a.p+a.len+1,p+1);
		return *this;
	}
	friend hull max(hull a,hull b){
		vector *c=alloc(B*2+1);int len=1;
		std::merge(a.p+1,a.p+a.len+1,b.p+1,b.p+b.len+1,c+1,
			[](const vector& a,const vector& b){return a.x<b.x||(a.x==b.x&&a.y>b.y);});
		for(int i=2;i<=a.len+b.len;i++)
			if(c[i].x!=c[len].x){
				while(len>1&&(c[len]-c[len-1])*(c[i]-c[len])>0) --len;
				c[++len]=c[i];
			}
		return {c,len};
	}
	ll cut(ll k){
		ll ret=std::max(0ll,p[len].cut(k));
		int left=1,right=len-1;
		while(left<right){
			int mid=(left+right)>>1;
			if((p[mid+1]-p[mid]).k()>k) left=mid+1;
			else right=mid;
		}
		if(left) ret=std::max(ret,p[left].cut(k));
		return ret;
	}
	ll max(){
		ll ret=0;
		for(int i=1;i<=len;i++) ret=std::max(ret,p[i].y);
		return ret;
	}
};
struct data{
	vector sum;
	hull mps,mss,mis;
	void pushup(const data& a,const data& b){
		sum=a.sum+b.sum;
		mps=max(a.mps,b.mps+a.sum);clear();
		mss=max(b.mss,a.mss+b.sum);clear();
		mis=max(max(a.mis,b.mis),a.mss+b.mps);clear();
	}
	void init(int x){
		sum=mps.p[mps.len=1]=mss.p[mss.len=1]=mis.p[mis.len=1]={1,x};
	}
	void pushtag(int tag){
		sum.plusf(tag);
		mps.plusf(tag);
		mss.plusf(tag);
		mis.plusf(tag);
	}
}t[B*4];
struct _data{
	ll sum,mps,mss,mis;
	_data operator+(const _data& b)const{
		return _data(sum+b.sum,std::max(mps,sum+b.mps),std::max(mss+b.sum,b.mss),std::max(std::max(mis,b.mis),mss+b.mps));
	}
	_data operator+=(const _data& b){
		return *this=*this+b;
	}
	_data(){}
	_data(ll sum,ll mps,ll mss,ll mis):sum(sum),mps(mps),mss(mss),mis(mis){}
	_data(data b):sum(b.sum.y),mps(b.mps.max()),mss(b.mss.max()),mis(b.mis.max()){}
	_data(data b,ll k):sum(b.sum.y),mps(b.mps.cut(k)),mss(b.mss.cut(k)),mis(b.mis.cut(k)){}
}ans[N];
ll tag[B*4];
vector MIS[LB][B],MPS[LB][B],MSS[LB][B];
void build(int a[],int d,int l,int r,int o){
	t[o].mis.p=MIS[d]+l-1;
	t[o].mps.p=MPS[d]+l-1;
	t[o].mss.p=MSS[d]+l-1;
	tag[o]=0;
	if(l==r) return t[o].init(a[l]);
	int mid=(l+r)>>1;
	build(a,d+1,l,mid,o<<1);
	build(a,d+1,mid+1,r,o<<1|1);
	t[o].pushup(t[o<<1],t[o<<1|1]);
}
void push(int o,int tg){
	tag[o]+=tg;
	t[o].pushtag(tg);
}
void pushdown(int o){
	if(tag[o]){
		push(o<<1,tag[o]);
		push(o<<1|1,tag[o]);
		tag[o]=0;
	}
}
void update(int L,int R,int x,int l,int r,int o){
	if(L<=l&&r<=R) return push(o,x);
	int mid=(l+r)>>1;pushdown(o);
	if(L<=mid) update(L,R,x,l,mid,o<<1);
	if(mid<R) update(L,R,x,mid+1,r,o<<1|1);
	t[o].pushup(t[o<<1],t[o<<1|1]);
}
_data query(int L,int R,int l,int r,int o){
	if(L<=l&&r<=R) return t[o];
	int mid=(l+r)>>1;pushdown(o);
	if(L<=mid&&mid<R) return query(L,R,l,mid,o<<1)+query(L,R,mid+1,r,o<<1|1);
	if(L<=mid) return query(L,R,l,mid,o<<1);
	if(mid<R) return query(L,R,mid+1,r,o<<1|1);
	exit(114514);
}
struct operate{
	int type,l,r,x;
}opt[N];
std::vector<operate> op;
void calculate(int a[],int n){
	build(a,0,1,n,1);
	ll whole_tag=0;
	for(auto[type,l,r,x]:op){
		switch(type){
		case 1:
			if(l==1&&r==n) whole_tag+=x;
			else push(1,whole_tag),whole_tag=0,update(l,r,x,1,n,1);
			break;
		case 2:
			if(l==1&&r==n) ans[x]+=_data(t[1],-whole_tag);
			else push(1,whole_tag),whole_tag=0,ans[x]+=query(l,r,1,n,1);
			break;
		}
	}
}
int a[N];
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	int b=sqrt(n),bh=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&opt[i].type,&opt[i].l,&opt[i].r);
		if(opt[i].type==1) scanf("%d",&opt[i].x);
		else opt[i].x=++bh;
	}
	for(int i=0;i*b+1<=n;i++){
		op.clear();int L=i*b+1,R=std::min((i+1)*b,n);
		for(int j=1;j<=m;j++){
			if(opt[j].l<=R&&opt[j].r>=L){
//				printf("BLOCK %d %d\n",i,j);
				op.push_back(opt[j]);
				op.back().l=(std::max(op.back().l,L)-1)%b+1;
				op.back().r=(std::min(op.back().r,R)-1)%b+1;
			}
		}
		calculate(a+i*b,std::min(b,n-i*b));
	}
	for(int i=1;i<=bh;i++) printf("%lld\n",ans[i].mis);
}
