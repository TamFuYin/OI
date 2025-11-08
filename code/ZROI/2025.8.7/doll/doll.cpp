#include<bits/stdc++.h>
const int N=1e5;
int a[N];
int c[N];
int n;
bool check(int mid){
	int res=0;
	for(int i=n-1;i>=0;i--)
		res=std::max(0,c[i]+res-mid);
	return res==0;
}
int main(){
	freopen("doll.in","r",stdin);
	freopen("doll.out","w",stdout);
	scanf("%d",&n);
	int ans=1;
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		++c[a[i]];
		while(!check(ans)) ++ans;
		printf("%d ",ans);
	}
}
