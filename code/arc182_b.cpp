#include<cstdio>
const int N=2e5;
int top,a[N];
void dfs(int n,int k,int s){
	if(k==0||n==0){
		while(n--) a[++top]=s;
		return;
	}
	dfs(n/2,k-1,s);
	dfs((n+1)/2,k-1,s|1<<k-1);
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,k;scanf("%d%d",&n,&k);
		top=0;dfs(n,k-1,1<<k-1);
		for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
	}
}
