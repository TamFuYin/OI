#include<bits/stdc++.h>
//int r[5],l[5];
//void make(int X,int x[]){
//	for(int i=0;i<5;i++)
//		x[i]=X%10,X/=10;
//}
int dist(int x,int y){
	int ret=0;
	for(int i=0;i<5;i++)
		ret+=x%10!=y%10,x/=10,y/=10;
	return ret;
}
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
const int N=1e5,MOD=998244353;
using ll=long long;
struct _hash{
	std::size_t operator()(const std::pair<std::pair<int,int>,bool>& x)const{
		return (1ll*(x.first.first-1)*N+x.first.second-1)*2+x.second;
	}
};
std::unordered_map<std::pair<std::pair<int,int>,bool>,int,_hash> f;
#define mp std::make_pair
int dfs(int l,int r,int k,int bound){
	if(l>=r) return 0;
	if(bound<=0) return bound;
	if(f.find(mp(mp(l,r),k))!=f.end()) return f[mp(mp(l,r),k)];
	int ret=INT_MAX;
	std::vector<int> a[5];
	for(int i=l;i<=r;i++)
		a[dist(k?r+1:l-1,i)].push_back(i);
	for(int j=0;j<5;j++){
		for(int i:a[j]){
			int v=std::max(dfs(l,i-1,1,ret-(1+j)),
				dfs(i+1,r,0,ret-(1+j)));
			ckmin(ret,1+j+v);
		}
	}
	return f[mp(mp(l,r),k)]=ret;
}
int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		int L,R;scanf("%d%d",&L,&R);
		if(L==R) {puts("0");continue;}
		int ans=INT_MAX;
		for(int i=L;i<=R;i++){
			int d=1+dist(0,i),v=std::max(dfs(L,i-1,1,ans-d),dfs(i+1,R,0,ans-d));
			ckmin(ans,d+v);
		}
		printf("%d\n",ans);
	}
}
