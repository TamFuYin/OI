#include<bits/stdc++.h>
const int N=2e5+10,MOD=998244353;
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
struct pair{
    int T,invp;double v;
    bool operator<(const pair& b)const{
        return v<b.v;
    }
}a[N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1,A,B;i<=n;i++){
        scanf("%d%d%d",&a[i].T,&A,&B);
        a[i].v=a[i].T/(1-1.*A/B);
        a[i].invp=1ll*B*qpow(A,MOD-2)%MOD;
    }
    std::sort(a+1,a+n+1);
    int x=0;
    for(int i=1;i<=n;i++)
        x=1ll*(x+a[i].T)*a[i].invp%MOD;
    printf("%d",x);
}