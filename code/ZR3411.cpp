#include<bits/stdc++.h>
const int N=1<<20,MOD=998244353,HALF=(MOD+1)/2;
using ll=long long;
void FWT(int f[],int opt=1){
	if(opt==-1) opt=HALF;
	for(int m=2;m<=N;m*=2){
		for(int i=0;i<N;i+=m){
			for(int j=i;j<i+m/2;j++){
				int u=f[j],t=f[j+m/2];
				f[j]=1ll*(u+t)*opt%MOD;
				f[j+m/2]=1ll*(u-t+MOD)*opt%MOD;
			}
		}
	}
}
int f[N],g[N];
int main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
	int n;scanf("%d",&n);
    std::fill(g,g+N,1);
    for(int i=1;i<=n;i++){
        int l,r;scanf("%d%d",&l,&r);
        memset(f,0,sizeof f);
        for(int j=l;j<=r;j++) f[j]=1;
        FWT(f);
        for(int j=0;j<N;j++) g[j]=1ll*g[j]*f[j]%MOD;
    }
    FWT(g,-1);
    printf("%d",g[0]);
}