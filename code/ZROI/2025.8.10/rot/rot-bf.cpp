#include<bits/stdc++.h>
const int N=10;
int a[N];
int n=6;
int cnt[N];
#define ckmin(a,b) a=std::min(a,b)
int ans;
void solve(int k=0){
	if(k==n) return;
	bool YES=1;
	for(int i=1;i<=n;i++) YES&=a[i]==i;
	if(YES) ckmin(ans,k);
	for(int i=1;i<=n;i++){
		int tmp=a[1];
		for(int j=1;j<i;j++) a[j]=a[j+1];
		a[i]=tmp;
		solve(k+1);
		for(int j=i-1;j>=1;j--) a[j+1]=a[j];
		a[1]=tmp;
	}
}
int AC(){
	int d=a[n],k=n-1;
	for(int i=n-1;i>=1;i--){
		if(a[i]>d||a[i]>a[i+1]) break;
		--k;
	}
	return k;
}
int main(){
//	int n,m;scanf("%d%d",&n,&m);
	std::iota(a+1,a+n+1,1);
	do{
//		for(int i=1;i<=n;i++) printf("%d ",a[i]);printf(": ");
		ans=1e9;solve();
		assert(ans==AC());
//		printf("%d %d\n",ans,AC());
	}while(std::next_permutation(a+1,a+n+1));
}
