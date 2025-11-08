#include<bits/stdc++.h>
const int MOD=998244353;
const int N=1e6+10;
int f[N];
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%MOD;
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return res;
}
int f1(int x){return x&1?MOD-1:1;}
int s[N];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        f[i]=1ll*qpow(m,i)*s[i/2]%MOD;
        s[i]=(s[i-1]+1ll*(qpow(m,i)+MOD-f[i])*qpow(m,MOD-1-2*i))%MOD;
    }
    printf("%d\n",(f[n]+MOD-(n%2==0)*(qpow(m,n/2)+MOD-f[n/2])%MOD)%MOD);
}