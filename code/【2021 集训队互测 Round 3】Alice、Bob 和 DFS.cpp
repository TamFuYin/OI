#include<bits/stdc++.h>
const int N=1e5;
int c[N],f[N];
std::vector<int> to[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	for(int i=1;i<=n;i++){
		int m;scanf("%d",&m);
		to[i].resize(m);
		for(int j=0;j<m;j++)
			scanf("%d",&to[i][j]);
	}
	for(int i=n;i>=1;i--){
		if(c[i]){
			f[i]=exist(i,0)
		}
	}
}
