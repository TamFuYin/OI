#include<bits/stdc++.h>
int main(){
    // freopen("ex_dis1.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n,u,v;scanf("%d%d%d",&n,&u,&v);
        auto fa=[&n](int y){
            return ((y-n)%y+y)%y;
        };
        using ll=long long;
        std::map<int,ll> mp;
        ll cur=0;
        while(u){
            mp.insert({u,cur});
            cur+=1ll*u*fa(u);
            u=fa(u);
        }
        cur=0;
        while(v&&mp.find(v)==mp.end()){
            cur+=1ll*v*fa(v);
            v=fa(v);
        }
        if(!v) puts("-1");
        else printf("%lld\n",cur+mp[v]);
    }
}