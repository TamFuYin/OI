#pragma GCC optimize(3)
#include<bits/stdc++.h>
using ll=long long;
using ull=unsigned long long;
std::mt19937 rnd(time(0));
ll qmul(ull a,ull b,ull mod){
    return (__int128)a*b%mod;
}
ll qpow(ll a,ll b,ll mod){
    ll ans=1;
    for(;b;b>>=1){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
    }
    return ans;
}
bool MillerRabin(ll p){
    if(p<2) return 0;
    if(p<=3) return 1;
    ll d=p-1,r=0;
    while(!(d&1)) ++r,d>>=1;
    for(ll k=0;k<10;k++){
        ll a=rnd()%(p-2)+2,
        x=qpow(a,d,p);
        if(x==1||x==p-1) continue;
        for(int i=0;i<r-1;++i){
            x=x*x%p;
            if(x==p-1) break;
        }
        if(x!=p-1) return 0;
    }
    return 1;
}
ll PollardRho(ll x){
    ll t=0,c=rnd()%(x-1)+1,s=t;
    int step=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1){
        for(step=1;step<=goal;++step){
            t=(qmul(t,t,x)+c)%x;
            val=qmul(val,abs(t-s),x);
            if(!val) return x;
            if(step%127==0){
                ll d=std::__gcd(val,x);
                if(d>1) return d;
            }
        }
        ll d=std::__gcd(val,x);
        if(d>1) return d;
    }
}
std::map<ll,int> cnt;
const int N=200,MOD=1e9+7;
int S,a[N],b[N],c[N];
struct vector{
    int a[N];
    void print(){
        for(int i=0;i<S;i++)
            printf("%d ",a[i]);
        puts("");
    }
};
struct matrix{
    int a[N][N];
    matrix operator*(const matrix& b)const{
        matrix c;memset(c.a,0,sizeof c.a);
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    c.a[i][j]=(c.a[i][j]+1ll*a[i][k]*b.a[k][j])%MOD;
                }
            }
        }
        return c;
    }
    vector operator*(const vector& b)const{
        vector c;memset(c.a,0,sizeof c.a);
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                c.a[i]=(c.a[i]+1ll*a[i][j]*b.a[j])%MOD;
            }
        }
        return c;
    }
    void print(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++)
                printf("%d ",a[i][j]);
            puts("");
        }
    }
}A[61];
// void factor(ll m){
//     if(m==1) return;
//     if(MillerRabin(m)){
//         ++cnt[m];
//         return;
//     }
//     ll p=PollardRho(m);
//     while(p==m||p==0)
//         p=PollardRho(m);
//     factor(p);
//     factor(m/p);
// }
const int V=1e6+10;
std::vector<int> pr;
std::bitset<V> ispr;
void factor(ll m){
    for(int i:pr) while(m%i==0) ++cnt[i],m/=i;
    if(m==1) return;
    if(MillerRabin(m)) {++cnt[m];return;}
    ll sq=sqrt(m);
    if(sq*sq==m) {cnt[sq]+=2;return;}
    ++cnt[1145141919810];
    ++cnt[350234'350235];
}
int t,mx;
int fac[N+1],ifac[N+1];
int mem[N][N];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
int lpow(int a,int b){
    if(!mem[a][b]) mem[a][b]=qpow(a,b);
    return mem[a][b];
}
void preTask(){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);
    for(int i=N-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    ispr.set();ispr.reset(0);ispr.reset(1);
    for(int i=2;i<V;i++){
        if(ispr[i]) pr.push_back(i);
        for(int j:pr){
            if(1ll*i*j>=V) break;
            ispr[i*j]=0;
            if(i%j==0) break;
        }
    }
}
int binom(int n,int k){
    if(k<0||k>n) return 0;
    return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
vector origin(){
    vector v;
    for(int s=0;s<S;s++){
        int x=s;v.a[s]=1;
        for(int i=1;i<=mx;i++){
            int c=x%(b[i]+1);
            v.a[s]=1ll*v.a[s]*binom(b[i],c)%MOD*lpow(i,c)%MOD;
            x/=b[i]+1;
        }
    }
    return v;
}
int cal(int s1,int s2){
    int tot=1,res=1;
    for(int i=1;i<=mx;i++){
        int c1=s1%(b[i]+1),c2=s2%(b[i]+1);
        res=1ll*res*binom(b[i]-c1,c2)%MOD*lpow(i,c2)%MOD;
        tot=1ll*tot*binom(b[i],c2)%MOD*lpow(i,c2)%MOD;
        s1/=b[i]+1,s2/=b[i]+1;
    }
    return (tot+MOD-res)%MOD;
}
int solve(ll n){
    vector x=origin();
    for(int i=60;i>=0;i--)
        if(n>>i&1) x=A[i]*x;
    int ans=0;
    for(int i=0;i<S;i++) (ans+=x.a[i])%=MOD;
    return ans;
}
int main(){
    preTask();
    // freopen("gen1.in","r",stdin);
    // freopen("gen.out","w",stdout);
    int C,T;scanf("%d%d",&C,&T);
    while(T--){
        ll m;int q;scanf("%lld%d",&m,&q);
        cnt.clear();factor(m);
        t=mx=0;S=1;
        for(auto p:cnt) c[t++]=p.second,mx=std::max(mx,p.second),
        // printf("%lld %d\n",p.first,p.second);
        std::fill(b,b+mx+1,0);
        for(int i=0;i<t;i++) ++b[c[i]];
        for(int i=1;i<=mx;i++) S*=b[i]+1;
        for(int i=0;i<S;i++)
            for(int j=0;j<S;j++)
                A[0].a[i][j]=cal(j,i);
        for(int i=1;i<=60;i++) A[i]=A[i-1]*A[i-1];
        while(q--){
            ll n;scanf("%lld",&n);
            printf("%d\n",solve(n-1));
        }
    }
}
