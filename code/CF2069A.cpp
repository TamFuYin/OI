#include<bits/stdc++.h>
const int N=1e5+10;
int b[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		int last=0;
		for(int i=2;i<n;i++) scanf("%d",b+i);
		for(int i=3;i<n-1;i++) if(!b[i]&&(b[i-1]&b[i+1])) {puts("NO");goto flag;}
		puts("YES");
		flag:;
	}
}