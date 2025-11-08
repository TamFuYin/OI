#include<bits/stdc++.h>
const int N=190,M=sqrt(N);
char s[N][N];
int f[(int)(N*pow(3,M))];
int main(){
	int n,m;scanf("%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",s[i]);
	if(m>n){
		static char _[N][N];
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) _[i][j]=s[i][j];
		std::swap(n,m);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) s[i][j]=_[j][i];
	}
}