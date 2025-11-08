#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int INF=1e9,N=1e2+10;
const int N=1e5;
int a[N];
int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	bool need=0;
	for(int i=1;i<=n;i++) need|=a[i]>m;
	if(!need){
		puts("0");
		return 0;
	}
	if(k==1) puts("1");
	else if(k==2){
		bool gr=0;
		for(int i=1;i<=n;i++)
			if(i&1) gr|=a[i]>m;
		if(!gr[0]||a[1]<=m&&!gr[1])
	}
}