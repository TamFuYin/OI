#include<bits/stdc++.h>
using ll=long long;
template<typename T>
void ckmin(T& a,T b){
    a=std::min(a,b);
}
template<typename T>
void ckmax(T& a,T b){
    a=std::max(a,b);
}
struct line{
    ll k,b;
    ll f(ll x){
        return b+k*x;
    }
    line operator-(){
        return {-k,-b};
    }
};
const int N=1e5+10,MAXT=1e9;
line t[N*100];int size,rt,ls[N*100],rs[N*100];
void ins(line p,int l,int r,int& o){
    if(!o){
        t[o=++size]=p;
        return;
    }
    int mid=l+r>>1;line& q=t[o];
    if(q.f(mid)<p.f(mid)) std::swap(p,q);
    if(p.f(l)>q.f(l)) ins(p,l,mid,ls[o]);
    if(p.f(r)>q.f(r)) ins(p,mid+1,r,rs[o]);
}
void insert(int L,int R,line p,int l=0,int r=MAXT,int& o=rt){
    if(!o) o=++size;
    if(L<=l&&r<=R) return ins(p,l,r,o);
    int mid=l+r>>1;
    if(L<=mid) insert(L,R,p,l,mid,ls[o]);
    if(mid<R) insert(L,R,p,mid+1,r,rs[o]);
}
ll query(int x,int l=0,int r=MAXT,int o=rt){
    if(!o) return 0;
    int mid=l+r>>1;ll ret=t[o].f(x);
    if(x<=mid) ckmax(ret,query(x,l,mid,ls[o]));
    else ckmax(ret,query(x,mid+1,r,rs[o]));
    return ret;
}
std::vector<std::pair<int,line> > l[N];
std::vector<int> Q;
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int a;scanf("%d",&a);
        l[i].emplace_back(0,line{0,a});
    }
    while(m--){
        int t;char s[10];
        scanf("%d%s",&t,s);
        if(s[0]=='c'){
            int k,x;scanf("%d%d",&k,&x);
            l[k].emplace_back(t,line{x,l[k].back().second.f(t)-1ll*x*t});
        }
        else Q.push_back(t);
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<l[i].size();j++){
            int L=l[i][j].first,R=j==l[i].size()-1?MAXT:l[i][j+1].first;
            insert(L,R,l[i][j].second);
            insert(L,R,-l[i][j].second);
        }
    for(int i:Q) printf("%lld\n",query(i));
}