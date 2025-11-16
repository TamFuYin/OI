#include<bits/stdc++.h>
const int MOD=998244353;
const int N=1<<19;
int rev[N];
int fac[N],ifac[N];
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%MOD;
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return res;
}
void preTask(){
    fac[0]=1;
    for(int i=1;i<N;i++)
        fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N-1]=qpow(fac[N-1],MOD-2);
    for(int i=N-2;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    for(int i=0;i<N;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)?(N>>1):0);
}
using ll=long long;
void NTT(int f[],int inv=0){
    for(int i=0;i<N;i++) if(i<rev[i]) std::swap(f[i],f[rev[i]]);
    for(int m=2;m<=N;m*=2){
        const int wm=qpow(3,(MOD-1)/m);
        for(int i=0;i<N;i+=m){
            int w=1;
            for(int j=i;j<i+m/2;j++,w=(ll)w*wm%MOD){
                int u=f[j],t=(ll)f[j+m/2]*w%MOD;
                f[j]=(u+t)%MOD;
                f[j+m/2]=(u-t+MOD)%MOD;
            }
        }
    }
    if(inv){
        std::reverse(f+1,f+N);
        int iN=qpow(N,MOD-2);
        for(int i=0;i<N;i++) f[i]=1ll*f[i]*iN%MOD;
    }
}
void conv(int h[],int f[],int g[]){
    NTT(f);
    NTT(g);
    for(int i=0;i<N;i++) h[i]=1ll*f[i]*g[i]%MOD;
    NTT(h,1);
}
int x[N],y[N],a[N],b[N],c[N],f[N];
int main(){
    preTask();
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d%d",x+i,y+i),x[i]=(x[i]%MOD+MOD)%MOD,y[i]=(y[i]%MOD+MOD)%MOD;
    std::reverse(y+1,y+n);
    conv(x,x,y);
    for(int i=0;i<n;i++) c[n-1-i]=((x[-i+n]+x[-i+2*n])%MOD+(MOD-(x[i]+x[i+n])%MOD))%MOD;
    for(int i=0;i<n-1;i++) a[i]=1ll*c[i]*fac[i]%MOD,b[i]=ifac[i];
    std::reverse(a,a+n-1);
    conv(a,a,b);
    for(int i=0;i<n;i++) f[i]=1ll*a[n-2-i]*ifac[i]%MOD;
    for(int i=1;i<n-1;i++) printf("%d\n",f[i]);
}