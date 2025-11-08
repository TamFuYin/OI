#include<bits/stdc++.h>
const int N=15,S=1<<N;
std::bitset<N*(N-1)> out[S],in[S];
int f[S],g[S];
const int MOD=1e9+7;
int cnt(int s,int t){return (out[s]&in[t]).count();}
int lowbit(int x){return x&-x;}
int pow2[N*N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	pow2[0]=1;for(int i=1;i<=m;i++) pow2[i]=pow2[i-1]*2%MOD;
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		for(int s=1;s<(1<<n);s++){
			if(s>>u-1&1) out[s].set(i-1);
			if(s>>v-1&1) in[s].set(i-1);
		}
	}
	for(int s=1;s<(1<<n);s++){
		f[s]=pow2[cnt(s,s)];
//		printf(">>> %d\n",f[s]);
		for(int t=(s-1)&s;t;t=(t-1)&s)
			if(lowbit(s)==lowbit(t)) g[s]=(g[s]-1ll*f[t]*g[s-t]%MOD+MOD)%MOD;
		for(int t=s;t;t=(t-1)&s)
			f[s]=(f[s]-1ll*g[t]*pow2[cnt(s-t,t)+cnt(s-t,s-t)]%MOD+MOD)%MOD;
		g[s]=(g[s]+f[s])%MOD;
//		printf("%d %d %d\n",s,f[s],g[s]);
	}
	printf("%d",f[(1<<n)-1]);
}
