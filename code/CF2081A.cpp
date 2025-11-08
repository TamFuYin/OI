#include<bits/stdc++.h>
const int N=1e5;
double f[N];
int main(){
	int n;scanf("%d",&n);
	f[1]=0;
	for(int i=2;i<=n;i++) f[i]=(f[i/2]+f[(i+1)/2])/2+1;
	for(int i=1;i<=n;i++) printf("%d: %lf\n",i,f[i]);
}