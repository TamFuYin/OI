#include<bits/stdc++.h>
const int N=1e5;
int a[N];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		int ans=0;
		for(int i=2;i<=n;i++)
			if(a[i]<=a[i-1]) ++ans;
		printf("%d\n",ans);
	}
}