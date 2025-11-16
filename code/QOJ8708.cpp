#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
using ll=long long;
ll solve(std::map<int,std::vector<int> >& m){
    int las,g1=0,g2=0;
    for(auto& p:m){
        if(p.first!=m.begin()->first){
            if(p.first-las==1) return 1;
            g1=std::__gcd(g1,p.first-las);
        }
        las=p.first;
        auto& v=p.second;
        std::sort(ALL(v));
        for(int i=1;i<v.size();i++) g2=std::__gcd(g2,v[i]-v[i-1]);
    }
    return !g1||!g2?LLONG_MAX:1ll*g1*g2;
}
std::map<int,std::vector<int> > mx,my;
int main(){
    // freopen64(".in","r",stdin);
    int n;scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        mx[x].push_back(y);
        my[y].push_back(x);
    }
    ll ans=std::max(solve(mx),solve(my));
    printf("%lld",ans==LLONG_MAX?-1:ans);
}