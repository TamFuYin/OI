#include<bits/stdc++.h>
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		puts((n==1||m==1||n==2&&m==2)?"NO":"YES");
	}
}
