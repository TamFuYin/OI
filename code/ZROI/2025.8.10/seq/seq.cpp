#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
#define mp std::make_pair
const int N=5e5+10;
int c[N],b[N];
std::vector<int> vc[N];
int s[N];
std::stack<int> sta;
struct inte{
	int l,r;
	bool operator<(const inte& b)const{
		return r<b.r;
	}
};
std::vector<inte> a;
int n;
int t[N*4],tag[N*4];
void pushup(int o){
	t[o]=std::min(t[o<<1],t[o<<1|1]);
}
void pushdown(int o){
	if(tag[o]!=0){
		tag[o<<1]+=tag[o],t[o<<1]+=tag[o];
		tag[o<<1|1]+=tag[o],t[o<<1|1]+=tag[o];
		tag[o]=0;
	}
}
void build(int l=1,int r=n,int o=1){
	tag[o]=0;
	if(l==r){
		t[o]=s[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
//	printf("%d,%d : %d\n",l,r,t[o]);
}
int getmin(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o];
	int mid=l+r>>1,ret=INT_MAX;pushdown(o);
	if(L<=mid) ckmin(ret,getmin(L,R,l,mid,o<<1));
	if(mid<R) ckmin(ret,getmin(L,R,mid+1,r,o<<1|1));
	return ret;
}
void plus(int L,int R,int x,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R){
		tag[o]+=x;
		t[o]+=x;
		return;
	}
	int mid=l+r>>1;pushdown(o);
	if(L<=mid) plus(L,R,x,l,mid,o<<1);
	if(mid<R) plus(L,R,x,mid+1,r,o<<1|1);
	pushup(o);
}
int main(){
//	freopen("seq.in","r",stdin);
//	freopen("seq.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) vc[i].clear();
		for(int i=1;i<=n;i++) scanf("%d",c+i),vc[c[i]].push_back(i);
		for(int i=1;i<=n;i++) scanf("%d",b+i),s[i]=s[i-1]+(1-2*b[i]);
		int ans=0;
		a.clear();
		for(int i=1;i<=n;i++){
			while(!sta.empty()) sta.pop();
			for(int j:vc[i]){
				if(!b[j]) sta.push(j);
				else if(!sta.empty()){
					a.push_back({sta.top(),j});
					sta.pop();
				}
			}
		}
//		printf(": %d\n",(int)a.size());
		build();
		int min=std::min(s[0]=0,getmin(1,n));
//		printf("ANS = %d\n",(n-s[n])/2+min);
		sort(a.begin(),a.end());
//		for(int i=1;i<=n;i++) printf("%d ",s[i]);puts("");
//		printf("min = %d\n",min);
		for(auto p:a){
//			printf(">> %d %d : %d\n",p.l,p.r,getmin(p.l,p.r-1));
			if(getmin(p.l,p.r-1)!=min)
				plus(p.l,p.r-1,-1),++ans;
		}
		printf("%d\n",ans);
	}
}
