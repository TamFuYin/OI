#include<bits/stdc++.h>
using ll=long long;
const ll INF=1e18;
const int N=2e5+10;
#define ckmax(a,b) a=std::max(a,b)
struct data{
	ll a[4][4];
	data(){
		for(int i=0;i<4;i++)
			for(int j=i;j<4;j++)
				a[i][j]=-INF;
	}
	data operator+(const data& b)const{
		data c{};
		for(int i=0;i<4;i++)
			for(int j=i;j<4;j++)
				c.a[i][j]=std::max(a[i][j],b.a[i][j]);
		for(int i=0;i<4;i++)
			for(int j=i;j<4;j++)
				for(int k=j+1;k<4;k++)
					ckmax(c.a[i][k],a[i][j]+b.a[j+1][k]);
		return c;
	}
	void print(){
		for(int i=0;i<4;i++){
			for(int j=i;j<4;j++){
				if(a[i][j]>-1e9){
					printf("[%d~%d: %lld]\n",i,j,a[i][j]);
				}
			}
		}
	}
}t[N*4];
ll tag[2][N*4];
int a[N],b[N];
ll s[N];
int n;
void pushup(int o){
	t[o]=t[o<<1]+t[o<<1|1];
}
void build(int l=1,int r=n,int o=1){
	if(l==r){
		t[o].a[0][0]=t[o].a[2][2]=b[l]-s[l-1];
		t[o].a[1][1]=t[o].a[3][3]=b[l]+s[l];
		t[o].a[0][1]=t[o].a[2][3]=2*b[l]+s[l]-s[l-1];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
	// printf("%d~%d:\n",l,r);t[o].print();
}
void pushtag(int k,int o,ll v){
	tag[k][o]+=v;
	for(int i=0;i<4;i++){
		for(int j=i,x=0;j<4;j++){
			x+=j%2==k;
			t[o].a[i][j]+=x*v;
		}
	}
}
void pushdown(int o){
	for(int k=0;k<=1;k++)
	if(tag[k][o]){
		pushtag(k,o<<1,tag[k][o]);
		pushtag(k,o<<1|1,tag[k][o]);
		tag[k][o]=0;
	}
}
void add(int k,int L,int R,int v,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R){
		pushtag(k,o,v);
		return;
	}
	int mid=l+r>>1;pushdown(o);
	if(L<=mid) add(k,L,R,v,l,mid,o<<1);
	if(mid<R) add(k,L,R,v,mid+1,r,o<<1|1);
	pushup(o);
}
data query(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o];
	int mid=l+r>>1;
	if(L<=mid&&mid<R) return query(L,R,l,mid,o<<1)+query(L,R,mid+1,r,o<<1|1);
	if(L<=mid) return query(L,R,l,mid,o<<1);
	if(mid<R) return query(L,R,mid+1,r,o<<1|1);
	exit(-1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	build();
	int q;scanf("%d",&q);
	while(q--){
		int op,p,x;scanf("%d%d%d",&op,&p,&x);
		switch(op){
			case 1:
			add(0,p+1,n,-(x-a[p]));
			add(1,p,n,x-a[p]);
			a[p]=x;
			break;
			case 2:
			add(0,p,p,x-b[p]);
			add(1,p,p,x-b[p]);
			b[p]=x;
			break;
			default:
			printf("%lld\n",query(p,x).a[0][3]);
		}
	}
}