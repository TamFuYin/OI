#include<bits/stdc++.h>
template<typename T>void ckmax(T &x,T y){if(x<y) x=y;}
template<typename T>void ckmin(T &x,T y){if(x>y) x=y;}
using ll=long long;
using pla=std::pair<ll,ll>;// People's Liberation Army
const ll INF=1e18;
const int N=2e6+10;
ll pow3[N];
int a[N];
struct data{
    ll x,y,z;bool t;int s;
    bool operator<(const data& b)const{
        return x<b.x||x==b.x&&(y<b.y||y==b.y&&t<b.t);
    }
};
std::vector<data> v[6];
void solve(int* begin,int* end,bool type){
    int*const a=begin;int n=end-begin;
    for(int s=0;s<pow3[n-1];s++){
        ll b[3]={a[0],0,0};
        for(int i=1;i<n;i++) b[s/pow3[i-1]%3]+=a[i];
        std::pair<ll,int> bb[3];
        for(int i=0;i<3;i++) bb[i]={b[i],i};
        if(type) for(int i=0;i<3;i++) bb[i].first*=-1;
        std::sort(bb,bb+3);
        int bp[3];for(int i=0;i<3;i++) b[i]=bb[i].first,bp[bb[i].second]=i;
        int rs=bp[0];for(int i=1;i<n;i++) rs+=bp[s/pow3[i-1]%3]*pow3[i];
        int p[3],t=0;std::iota(p,p+3,0);
        do v[t++].push_back({b[p[0]]-b[p[1]],b[p[1]]-b[p[2]],b[p[2]]-b[p[0]],type,rs});
        while(std::next_permutation(p,p+3));
    }
}
namespace BIT{
    int m;
    pla t[N];
    int lowbit(int x){return x&-x;}
    void add(int x,pla v){while(x<=m) ckmin(t[x],v),x+=lowbit(x);}
    pla ask(int x){pla res{INF,0};while(x) ckmin(res,t[x]),x-=lowbit(x);return res;}
    void clear(){std::fill(t+1,t+m+1,pla(INF,0));}
}
int n;
pla meet(std::vector<data>& v){
    auto meet=[](pla l,pla r)->pla{return {l.first-r.first,l.second+r.second*pow3[n/2]};};
    static ll lsh[N];int lcnt=0;
    for(auto& i:v) lsh[lcnt++]=i.y;
    std::sort(lsh,lsh+lcnt),lcnt=std::unique(lsh,lsh+lcnt)-lsh;
    for(auto& i:v) i.y=std::lower_bound(lsh,lsh+lcnt,i.y)-lsh+1;
    BIT::m=lcnt;
    std::sort(v.begin(),v.end());
    pla ans={INF,0};BIT::clear();
    for(auto& i:v)
        if(i.t) ckmin(ans,meet(BIT::ask(i.y),pla(i.z,i.s)));
        else BIT::add(i.y,pla(i.z,i.s));
    return ans;
}
int main(){
    pow3[0]=1;for(int i=1;i<30;i++) pow3[i]=pow3[i-1]*3;
    // freopen("cake.in","r",stdin);
    // freopen("cake.out","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    solve(a,a+n/2,0),solve(a+n/2,a+n,1);
    pla ans={INF,0};
    for(int i=0;i<6;i++) ckmin(ans,meet(v[i]));
    printf("%lld\n",ans.first);
    for(int i=0;i<n;i++) putchar("ABC"[ans.second/pow3[i]%3]);
    return 0;
}