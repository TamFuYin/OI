#include<bits/stdc++.h>
const int N=3e3+10,sqrtN=sqrt(N),K=16,MOD=998244353;
int a[N],b[N];
std::vector<int> p;
bool notp[N];
std::vector<int> t[N];
int f[1<<K],g[1<<K];
int rd[1<<K];
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%MOD;
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return res;
}
int main(){
    for(int i=2;i<sqrtN;i++){
        if(!notp[i]) p.push_back(i);
        for(int j:p){
            if(i*j>=sqrtN) break;
            notp[i*j]=1;
            if(i%j==0) break;
        }
    }
    for(int s=0;s<(1<<K);s++){
        rd[s]=1;
        for(int i=0;i<K;i++)
            if(s>>i&1) rd[s]=1ll*rd[s]*p[i]%MOD;
    }
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);int res=a[i];
        for(int j=0;j<p.size();j++){
            if(res%p[j]==0) b[i]|=1<<j;
            while(res%p[j]==0) res/=p[j];
        }
        t[res].push_back(i);
    }
    f[0]=1;
    for(int i=1;i<=3e3;i++){
        if(t[i].empty()) continue;
        int all=1;
        for(int r:t[i]) all=1ll*all*(1+a[r])%MOD;
        for(int s=0;s<(1<<K);s++) g[s]=1ll*f[s]*all%MOD;
        for(int r:t[i])
            for(int s=0;s<(1<<K);s++){
                int sbr=b[r]&(((1<<K)-1)^s);
                int inv=qpow(1+a[r],MOD-2);
                for(int t=sbr;t;t=(t-1)&sbr){
                    (g[s|t]+=(i>1?MOD-1ll:1ll)*f[s]%MOD*a[r]%MOD*rd[t]%MOD*all%MOD*inv%MOD)%=MOD;
                }
            }
        std::swap(f,g);
    }
    int ans=0;
    for(int s=0;s<(1<<K);s++)
        ans=(ans+(__builtin_popcount(s)&1?MOD-f[s]:f[s]))%MOD;
    printf("%d\n",ans);
    return 0;
}