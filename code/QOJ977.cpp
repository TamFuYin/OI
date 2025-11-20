#include<bits/stdc++.h>
const int N=3e3+10,M=N*N;
int P;
int f[N][N];
int fac[M+1],ifac[M+1],inv[M+1];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return ret;
}
void preTask(){
    fac[0]=1;for(int i=1;i<=M;i++) fac[i]=1ll*fac[i-1]*i%P;
    ifac[M]=qpow(fac[M],P-2);for(int i=M-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
    inv[1]=1;for(int i=2;i<=M;i++) inv[i]=1ll*(P-P/i)*inv[P%i]%P;
}
int main(){
    int n,m;scanf("%d%d%d",&n,&m,&P);
    preTask();f[1][1]=n*m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            (f[i+1][j]+=1ll*j*(n-i)*inv[j+1]%P*fac[(i+1)*j-1]%P*ifac[i*j-1]%P*f[i][j]%P)%=P;
            (f[i][j+1]+=1ll*i*(m-j)*inv[i+1]%P*fac[(j+1)*i-1]%P*ifac[i*j-1]%P*f[i][j]%P)%=P;
        }
    }
    printf("%d\n",f[n][m]);
}
/*
4 3 1000000007
483619254
但是输出应为 95800320
*/