#include<bits/stdc++.h>
const int K=6,S=1<<K,MOD=998244353;
struct matrix{
	int data[S+1][S+1];
	matrix(){memset(data,0,sizeof data);}
	matrix(int a[]){
		memset(data,0,sizeof data);
		for(int s=0;s<S;s++){
			for(int t=0;t<S;t++)
			if((s&t)==0){
				(data[s|t][s]+=a[t])%=MOD;
				(data[S][s]+=a[t])%=MOD;
			}
		}
		data[S][S]=1;
	}
};
matrix operator*(const matrix& a,const matrix& b){
	matrix ret;
	for(int i=0;i<=S;i++){
		for(int j=0;j<=S;j++){
			for(int k=0;k<=S;k++){
				(ret.data[i][k]+=1ll*a.data[i][j]*b.data[j][k]%MOD)%=MOD;
			}
		}
	}
	return ret;
}
matrix qpow(matrix a,long long b){
	matrix ret=a;b--;
	while(b){
		if(b&1) ret=ret*a;
		a=a*a;b>>=1;
	}
	return ret;
}
int a(int n,int p){
	int ret=0;
	while(n%p==0) n/=p,++ret;
	return ret;
}
const int p[]={2,3,5,7,11,13};
int f[S];
int main(){
	long long N;int M;
	scanf("%lld%d",&N,&M);
	for(int i=1;i<=M;i++){
		for(int s=0;s<S;s++){
			int tmp=1;
			for(int k=0;k<K;k++)
				if(s&1<<k) tmp*=a(i,p[k]);
			f[s]+=tmp;
		}
	}
	printf("%d",qpow(f,N).data[S][0]);
}
