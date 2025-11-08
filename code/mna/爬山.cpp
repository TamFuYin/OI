#include<bits/stdc++.h>
const int N=1e5,W=22;
char s[N][W];
int h[N][W];
int v[N];int w,n;
int cur[W];
const int MOD=1e9+7,B=114514;
std::unordered_map<int,std::pair<int,int> > map;
void dfs_L(int i){
	if(i==w/2){
		int sum=0,hash=(cur[i]+MOD)%MOD;
		for(int i=0;i<=w/2;i++) sum+=cur[i];
		sum=(sum+MOD)%MOD;
		for(int i=1;i<=n;i++){
			int cv=0;
			for(int j=0;j<=w/2;j++)
				cv+=std::abs(h[i][j]-cur[j]);
			hash=(1ll*hash*B+cv)%MOD;
//			printf(">>> %d\n",cv);
		}
//		printf(">>L %d\n",hash);
		(map[hash].first+=sum)%=MOD;
		map[hash].second++;
		return;
	}
	cur[i+1]=cur[i]+1;dfs_L(i+1);
	cur[i+1]=cur[i]-1;dfs_L(i+1);
}
int ans,t;
int qpow(int a,int b){
	int ret=1;while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}return ret;
}
void dfs_R(int i){
	if(i==w/2){
		int sum=0,hash=(cur[i]+MOD)%MOD;
		for(int i=w/2+1;i<=w;i++) sum+=cur[i];
		sum=(sum+MOD)%MOD;
		for(int i=1;i<=n;i++){
			int cv=0;
			for(int j=w/2+1;j<=w;j++)
				cv+=std::abs(h[i][j]-cur[j]);
			hash=(1ll*hash*B+v[i]-cv)%MOD;
//			printf(">>> %d\n",cv);
		}
//		printf(">>R %d %d,%d\n",hash,map[hash].first,map[hash].second);
		(ans+=(map[hash].first+1ll*sum*map[hash].second)%MOD)%=MOD;
		t+=map[hash].second;
		return;
	}
	cur[i-1]=cur[i]+1;dfs_R(i-1);
	cur[i-1]=cur[i]-1;dfs_R(i-1);
}
int main(){
	freopen("hill.in","r",stdin);
	freopen("hill.out","w",stdout);
	int T,id;scanf("%d%d",&T,&id);
	while(T--){
		scanf("%d%d",&w,&n);
		for(int i=1;i<=n;i++){
			scanf("%s%d",s[i],v+i);
			h[i][0]=0;
			for(int j=1;j<=w;j++)
				h[i][j]=h[i][j-1]+(s[i][j-1]=='U'?1:-1);
		}
		ans=t=0;map.clear();cur[0]=cur[w]=0;
		dfs_L(0);dfs_R(w);
//		printf("%d %d\n",ans,t);
		if(t==0) puts("-1");
		else ans=1ll*ans*qpow(t*w,MOD-2)%MOD,printf("%d\n",ans);
	}
}
