#include<bits/stdc++.h>
#define add(u,v) to[u].push_back(v)
const int N=1e5;
int al[N],ar[N];
std::vector<int> to[N];
struct data{
	int cnt,sum;
	data operator+(const data& b)const{
		return {cnt+b.cnt,sum+b.sum};
	}
	data operator*(const data& b)const{
		return {cnt*b.cnt,sum*b.cnt+b.sum*cnt};
	}
};
int lim;
int dfs(int u){
	data tmp={}
	for(int v:to[u]){}
}
int lsh[N],lshn;
int main(){
	int n,K;scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) scanf("%d%d",al+i,ar+i),lsh[lshn++]=al[i],lsh[lshn++]=ar[i]+1;
	std::sort(lsh,lsh+lshn);
	lshn=std::unique(lsh,lsh+lshn)-lsh;
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	for(int u=1;u<=n;u++){
		for(int i=0;i<lshn;i++){
			lim=lsh[i]+K;
			int tmp=0;
			for(int v:to[u]) tmp+=dfs(v,u)+{1,0};
			ans+=tmp*tmp;
		}
	}
	printf("%d",ans);
}