#include<bits/stdc++.h>
using LD=long double;
int main(){
	freopen("cycle.in","r",stdin);
	freopen("cycle.out","w",stdout);
	int a,b;scanf("%d%d",&a,&b);
	LD ans=0;
	for(int i=1;i<=a;i++) ans+=(LD)1/(2*i-1);
	for(int i=1;i<=b;i++) ans+=(LD)1/(2*a+i);
	printf("%.10Lf",ans);
}
