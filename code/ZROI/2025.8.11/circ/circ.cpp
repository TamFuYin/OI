#include<bits/stdc++.h>
const int N=3e6+10;
using ush=unsigned short;
using ldb=long double;
ush th[N];
const ldb PI=asin(1)*2;
int main(){
//	freopen("ex_circ3.in","r",stdin);
	freopen("circ.in","r",stdin);
	freopen("circ.out","w",stdout);
	int n;scanf("%d",&n);
	ldb ssin=0,sdsin=0,ans=0,the,sint;
	for(int i=1;i<=n;i++)
		scanf("%Lf",&the),th[i]=the*100+0.5;
	std::sort(th+1,th+n+1);
	for(int i=1;i<=n;i++){
		the=th[i]*PI/18000,sint=sin(the);
		ans+=cos(the)*((2*i-n)*ssin-2*sdsin);
		ssin+=sint,sdsin+=i*sint;
	}
	ssin=0,sdsin=0;
	for(int i=n;i>=1;i--){
		the=th[i]*PI/18000,sint=sin(the);
		ans+=cos(the)*((n+2*i)*ssin-2*sdsin);
		ssin+=sint,sdsin+=i*sint;
	}
	printf("%.6Lf",ans/2/pow(10,10));
}
