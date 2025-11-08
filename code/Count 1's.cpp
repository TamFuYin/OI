#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
int main(){
	int n;scanf("%d",&n);
	int min=0,max=0,mn=0,mx=0,sum=0;
	for(int i=1;i<=n;i++){
		int ai;scanf("%d",&ai);
		sum+=ai;
		ckmin(mn,i-2*sum+min);
		ckmax(mx,i-2*sum+max);
		ckmin(min,2*sum-i);
		ckmax(max,2*sum-i);
	}
	printf("%d",mx-mn+1);
}