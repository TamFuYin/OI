#include<bits/stdc++.h>
const int N=1e6+10,MOD=998244353;
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int fac[N+1],ifac[N+1];
int binom(int n,int k){
    if(n<0||k<0||n<k) return 0;
    return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int n;
int a[N];
int g[2][N];
void solve(int op){
	int lx=0,ly1=0,ly2=1,lv1=1,lv2=0;
	auto get=[&](int i,int j){return (1ll*lv1*binom(i-lx,j-ly1)+1ll*lv2*binom(i-lx,j-ly2))%MOD;};
	for(int i=1;i<n;i++)if(a[i]){
		int v1=get(i-1,n-a[i]),v2=get(i-1,i-a[i]);
		lx=i,ly1=n-a[i]+1,lv1=v1,ly2=i-a[i],lv2=v2;
	}
	for(int i=0;i<=n;++i) g[op][i]=get(n-1,n-i);
}
int main(){
    fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
    // freopen("Z_3011.in","r",stdin);
    // freopen("");
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=2*n-1;i++) scanf("%d",a+i);
        solve(0);
        for(int i=1;i<n;i++) a[i]=a[2*n-i];
        solve(1);
        int ans=0;
        for(int k=1;k<=n;k++) if(!a[n]||a[n]==k) (ans+=1ll*g[0][k]*g[1][k]%MOD)%=MOD;
        printf("%d\n",ans);
    }
}