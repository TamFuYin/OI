#include<bits/stdc++.h>
const int N=7,M=205;
int f[2][N][1<<N][2*N*M];
int b[M];char sb[M];
const int MOD=998244353;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int main(){
	freopen("card1.in","r",stdin);
//	freopen("card.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",sb+1);
		for(int j=1;j<=m;j++)
			b[j]=(sb[j]=='1')<<i;
	}
	f[0][n-1][0][0]=MOD-1;
	for(int i=1;i<=m;i++){
		memset(f[i&1],0,sizeof f[0]);
		for(int j=0;j<n;j++){
			int S=b[i-1]>>j|(b[i]&(1<<j)-1)<<n-j,li,lj;
			if(j) li=i,lj=j-1;
			else li=i-1,lj=n-1;
			for(int s=S;;s=(s-1)&S){
				for(int nb=0;nb<=(b[i]>>j&1);nb++){
					int t=s>>1|nb<<n-1,ac=int(j!=0&&(s>>n-1&1|nb))+int(i!=1&&(s&1|nb));
					for(int c=0;c<=2*n*m-n-m-ac;c++) (f[i&1][j][t][c+ac]+=nb?MOD-f[li&1][lj][s][c]:f[li&1][lj][s][c])%=MOD,
					printf("[%d %d %d %d : %d] <- [%d %d %d %d : %d]\n",i,j,t,c+ac,f[i&1][j][t][c+ac],li,lj,s,c,f[li&1][lj][s][c]);
				}
				if(!s) break;
			}
		}
	}
	int ans=0;
	for(int c=1;c<=2*n*m-n-m;c++){
		int tmp=0;
		for(int s=b[m];;s=(s-1)&b[m]){
			(tmp+=f[m&1][n-1][s][c])%=MOD;
			if(!s) break;
		}
		(ans+=1ll*tmp*qpow(c,MOD-2))%=MOD;
	}
	ans=1ll*ans*(2*n*m-n-m)%MOD;
	printf("%d",ans);
}
