#include<bits/stdc++.h>
const int N=2e5+10;
int a[N],b[N],max[N],min[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		bool b1=0,b0=1;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),b0&=a[i]==i;
		max[0]=-1e9;min[n+1]=1e9;
		for(int i=1;i<=n;i++) max[i]=std::max(max[i-1],a[i]);
		for(int i=n;i>=1;i--) min[i]=std::min(min[i+1],a[i]);
		if(b0) {puts("0");continue;}
		for(int i=1;i<=n;i++)
			if(max[i]==min[i]) b1=1;
		if(b1) {puts("1");continue;}
		if(a[1]!=n||a[n]!=1) puts("2");
		else puts("3");
	}
}
