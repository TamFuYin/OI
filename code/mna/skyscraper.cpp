#include<bits/stdc++.h>
const int N=1e5;
std::pair<int,int> a[N];
#define h first
#define w second
int pre[N];
int main(){
	freopen("skyscraper.in","r",stdin);
	freopen("skyscraper.out","w",stdout);
	int n,V;scanf("%d%d",&n,&V);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].h,&a[i].w);
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i].h;
	int ans=0;
	auto crs=[n](int s){return s*(pre[n]-s);};
	for(int i=1;i<n;i++){
		ans+=V*crs(pre[i]);
		for(int j=a[i].h;j>(a[i].h+1)/2;j--) ans+=a[i].w*crs(a[i].h-j+1);
		for(int j=(a[i].h+1)/2;j>(a[i-1].h+1)/2;j--) ans+=a[i].w*crs(j-1+pre[i-1]);
		for(int j=(a[i-1].h+1)/2;j>1;j--) ans+=a[i].w*crs(j-1);
	}
	for(int j=a[n].h;j>(a[n-1].h+1)/2;j--) ans+=a[n].w*crs(j-1+pre[n-1]);
	for(int j=(a[n-1].h+1)/2;j>1;j--) ans+=a[n].w*crs(j-1);
	printf("%d",ans);
}
