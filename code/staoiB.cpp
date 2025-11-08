#include<bits/stdc++.h>
const int N=3e5;
int a[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		std::sort(a+1,a+n+1);
		std::reverse(a+1,a+n+1);
		bool tag=0;int dda=0;
		while(n){
			if(n%2==1){
				--n;
			}
			else{
				if(a[n]-dda<=1) --n;
				else ++dda;
			}
			tag^=1;
		}
		puts(tag?"Alice":"Bob");
	}
}
