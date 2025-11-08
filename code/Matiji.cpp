#include<bits/stdc++.h>
const int N=2e5+10;
int p[N];
int n,s;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&s);
		for(int i=1;i<=n;i++) scanf("%d",p+i);
		for(int i=1;i<=n;i++){
			if(p[i]>s) s=ceil((p[i]+s)/2.0);
		}
		printf("%d\n",s);
	}
}
