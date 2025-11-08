#include<bits/stdc++.h>
const int N=1e5+10;
int p[N],q[N];
int run(int x){
    if(!p[x]) return 1;
    return run(p[x])+1;
}
const int MOD=998244353;
using ll=long long;
int qpow(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return c;
}
int inv(int x){return qpow(x,MOD-2);}
int solve(int n,int m){
	if(n&1) return 0;
	int ret=1;
	for(int i=1;i<=n+m;i++) ret=1ll*ret*i%MOD;
	for(int i=n-1;i>0;i-=2) ret=1ll*ret*i%MOD;
	for(int i=n;i>0;i-=2) ret=1ll*ret*qpow(i,MOD-2)%MOD;
	return ret;
}
int main(){
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",p+i),q[p[i]]=i;
    static int a[2]={0,0};
    for(int i=1;i<=n;i++) if(!q[i]) ++a[run(i)&1];
    printf("%d",solve(a[1],a[0]));
}
