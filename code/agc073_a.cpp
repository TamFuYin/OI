#include<bits/stdc++.h>
const int MOD=998244353;
int qpow(int a,int b){
    if(b<0) b+=MOD-1;
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int a[int(1e6+10)];
int main(){
    int L,K,N,I=0,V=0;scanf("%d%d%d",&L,&K,&N);
    for(int i=0;i<N;i++) scanf("%d",a+i),a[N+i]=a[i]+L;
    for(int i=0;i<N;i++){
        int c=std::lower_bound(a,a+N*2,a[i]+K)-a-i-1;
        (I+=c)%=MOD,V+=c==0;
    }
    printf("%d",int(1ll*(3*N+I+V)*qpow(2,N-3)%MOD));
}