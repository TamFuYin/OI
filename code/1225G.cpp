#include<bits/stdc++.h>
const int V=2000,N=16;
std::bitset<V+10> f[1<<N];
int a[N],b[N];int n,k;
void dfs(int s,int i,int dep=0){
//	printf("DFS %d %d %d\n",s,i,dep);
	if(s==0) return;
	if(i*k<=V&&f[s][i*k]) return dfs(s,i*k,dep+1);
	for(int j=0;j<n;j++) if(s>>j&1)
		if(i>=a[j]&&f[s^1<<j][i-a[j]])
			return b[j]=dep,dfs(s^1<<j,i-a[j],dep);
}
std::priority_queue<std::pair<int,int> > Q;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++) scanf("%d",a+i);
	f[0][0]=1;
	for(int s=1;s<(1<<n);s++){
		for(int i=0;i<n;i++)if(s>>i&1)
			f[s]|=f[s^1<<i]<<a[i];
		for(int i=V/k;i;i--) if(f[s][i*k]) f[s][i]=1;
	}
	if(!f[(1<<n)-1][1]) return puts("NO"),0;
	puts("YES");
	dfs((1<<n)-1,1);
	for(int i=0;i<n;i++) Q.emplace(b[i],a[i]);
	while(Q.size()>1){
		int b=Q.top().first,u=Q.top().second;Q.pop();
		printf("%d %d\n",u,Q.top().second);
		u+=Q.top().second;Q.pop();
		while(u%k==0) u/=k,--b;
		Q.emplace(b,u);
	}
}
