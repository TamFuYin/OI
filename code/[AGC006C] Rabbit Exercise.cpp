#include<bits/stdc++.h>
const int N=1e5;
int x[N];
int a[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",x+i);
	int m,k;scanf("%d%d",&m,&k);
	for(int i=1;i<=m;i++) scanf("%d",a+i);
	while(k--){
		for(int i=1;i<=m;i++)
			x[a[i]]=x[a[i]-1]+x[a[i]+1]-x[a[i]];
	}
	for(int i=1;i<=n;i++) printf("%d\n",x[i]);
}