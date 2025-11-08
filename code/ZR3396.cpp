#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define x first
#define y second
typedef long long ll;
typedef std::pair<ll,ll> pii;
const int N=2e5+10,M=N*40;
pii a[N];
template<typename T>
struct lsh{
	T a[M];
	int size;
	void ins(T b){
		a[size++]=b;
	}
	void make(){
		std::sort(a,a+size);
		size=std::unique(a,a+size)-a;
	}
	int g(T b)const{
		auto it=std::lower_bound(a,a+size,b);
		if(*it!=b) return -1;
		else return it-a;
	}
};
lsh<pii> lp;
lsh<ll> li;
std::vector<pii> son[M];
int dsiz[M];
int ssiz[M],siz[M];
bool cmp(const pii& a,const pii& b){
	if(a.x>a.y) return a.x>b.x;
	else return a.y>b.y;
}
pii getfa(pii p){
	if(p.x>p.y) return {p.x%p.y,p.y};
	else return {p.x,p.y%p.x};
}
void pre_gcd(pii p){
	lp.ins(p);
	if(!p.x||!p.y){
		li.ins(p.x+p.y);
		return;
	}
	pre_gcd(getfa(p));
}
void gcd(pii p){
	++siz[lp.g(p)];
	pii f=getfa(p);
	son[lp.g(f)].push_back(p);
	if(!f.x||!f.y) ++dsiz[li.g(f.x+f.y)];
	else gcd(f);
}
int main(){
	// freopen("ex_linear5.in","r",stdin);
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
		pre_gcd(a[i]);
	}
	li.make(),lp.make();
	for(int i=1;i<=n;i++) gcd(a[i]);
	for(int i=0;i<lp.size;i++){
		std::sort(ALL(son[i]),cmp);
		son[i].resize(std::unique(ALL(son[i]))-son[i].begin());
		int las=0;
		for(auto s:son[i]){
			ssiz[lp.g(s)]=las+=siz[lp.g(s)];
//			printf("%lld %lld: %d\n",s.x,s.y,ssiz[s]);
		}
	}
	while(q--){
		pii p;scanf("%lld%lld",&p.x,&p.y);
		pii f=getfa(p);
		if(p.x==p.y){
			if(li.g(p.x)==-1) puts("0");
			else printf("%d\n",dsiz[li.g(p.x)]);
		}
		else{
			if(lp.g(f)==-1||son[lp.g(f)].empty()) puts("0");
			else printf("%d\n",ssiz[lp.g(*--std::upper_bound(ALL(son[lp.g(f)]),p,cmp))]);
		}
	}
}