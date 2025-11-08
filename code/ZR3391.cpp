#include<bits/stdc++.h>
const int N=4e6+10;
int a[N];
int c[N];
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
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+2*i-1);
    int ans=0;
    for(int i=1;i<=2*n-1;i++){
        for(int i=1;i<=n*2;i++) c[a[i]]=0;
        int cnt=0;
        for(int j=i;j>=1&&2*i-j<=2*n-1;j--){
            if(!a[j]) continue;
            if(!c[a[j]]) c[a[j]]=a[2*i-j],++cnt;
            else if(c[a[j]]!=a[2*i-j]) break;
            if(!c[a[2*i-j]]) c[a[2*i-j]]=a[j],++cnt;
            else if(c[a[2*i-j]]!=a[j]) break;
            (ans+=qpow(m,m-cnt))%=MOD;
        }
    }
    printf("%d",ans);
}