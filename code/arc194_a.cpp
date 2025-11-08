#include<bits/stdc++.h>
const int N=2e5+10;
int a[N];
using ll=long long;
ll f[N],mx[2];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	mx[0]=0;mx[1]=LLONG_MIN;
	for(int i=1;i<=n;i++){
		f[i]=std::max(f[i-1]+a[i],mx[i&1]);
		mx[i&1]=std::max(mx[i&1],f[i]);
	}
	printf("%lld",f[n]);
}