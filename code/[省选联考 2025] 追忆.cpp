#include<bits/stdc++.h>
const int N=1e5+10,Ba=3e2,Bb=2e3;
using bits=std::bitset<N>;
std::vector<int> to[N];
bits ac[N];
int a[N],b[N];
int n,m,q;
bits sa[N/Ba+1],sb[N/Bb+1];
int pa[N],pb[N];
bits& solve_a(int l,int r){
	static bits ret;ret.reset();
	if((l-1)/Ba==(r-1)/Ba){
		for(int i=l;i<=r;i++) ret.set(pa[i]);
		return ret;
	}
	for(int i=l;i<=((l-1)/Ba+1)*Ba;i++) ret.set(pa[i]);
	for(int i=(r-1)/Ba*Ba+1;i<=r;i++) ret.set(pa[i]);
	return ret|=(sa[(r-1)/Ba]^sa[(l-1)/Ba+1]);
}
int solve_b(const bits& S){
	if(S.none()) return 0;
	int l=0,r=(n-1)/Bb;
	while(l<r){
		int mid=l+r+1>>1;
		if((sb[mid]&S).none()) r=mid-1;
		else l=mid;
	}
	for(int i=std::min((l+1)*Bb,n);i>l*Bb;i--)
		if(S[pb[i]]) return i;
	exit(-1);
}
std::string to_s(bits s){
	std::string tmp=s.to_string();
	return std::string(tmp.rbegin(),tmp.rend()).substr(1,n);
}
void erase_a(int x){
	for(int i=(a[x]-1)/Ba;i>=0;i--) sa[i].reset(x);
}
void ins_a(int x){
	for(int i=(a[x]-1)/Ba;i>=0;i--) sa[i].set(x);
}
void erase_b(int x){
	for(int i=(b[x]-1)/Bb;i>=0;i--) sb[i].reset(x);
}
void ins_b(int x){
	for(int i=(b[x]-1)/Bb;i>=0;i--) sb[i].set(x);
}
int main(){
//	freopen("recall3.in","r",stdin);
//	freopen("recall3.out","w",stdout);
	int c,T;scanf("%d%d",&c,&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=n;i++) to[i].clear();
		for(int i=1,u,v;i<=m;i++)
			scanf("%d%d",&u,&v),
			to[u].push_back(v);
		for(int u=n;u>=1;u--){
			ac[u].reset();
			ac[u].set(u);
			for(int v:to[u])
				ac[u]|=ac[v];
		}
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		for(int i=1;i<=n;i++) scanf("%d",b+i);
		for(int i=0;i<=(n-1)/Ba;i++) sa[i].reset();
		for(int i=0;i<=(n-1)/Bb;i++) sb[i].reset();
		for(int i=1;i<=n;i++){
			sa[(a[i]-1)/Ba].set(i);
			sb[(b[i]-1)/Bb].set(i);
		}
		for(int i=(n-1)/Ba-1;i>=0;i--) sa[i]|=sa[i+1];
		for(int i=(n-1)/Bb-1;i>=0;i--) sb[i]|=sb[i+1];
		for(int i=1;i<=n;i++) pa[a[i]]=pb[b[i]]=i;
		for(int i=1;i<=q;i++){
			int o,x,y,l,r;
			scanf("%d",&o);
			switch(o){
				case 1:
				scanf("%d%d",&x,&y);
				erase_a(x);erase_a(y);
				std::swap(a[x],a[y]);
				pa[a[x]]=x,pa[a[y]]=y;
				ins_a(x);ins_a(y);
				break;
				case 2:
				scanf("%d%d",&x,&y);
				erase_b(x);erase_b(y);
				std::swap(b[x],b[y]);
				pb[b[x]]=x,pb[b[y]]=y;
				ins_b(x);ins_b(y);
				break;
				default:
				scanf("%d%d%d",&x,&l,&r);
				printf("%d\n",solve_b(ac[x]&solve_a(l,r)));
				break;
			}
		}
	}
}
