#include<bits/stdc++.h>
using ll=long long;
int safelg(ll x){
    if(x==1) return 0;
    return std::__lg(x);
}
ll calc(ll l, ll r) {
    // cout << "calc" << l << ' ' << r << endl;
    if (r < l) return 0;
    assert(l <= r);
    if (r == l) return 1;
    if (safelg(l) == safelg(r)) {
        return (r - l + 1);
    }
    if (safelg(l) + 1 == safelg(r)) {
        int k = safelg(r);
        return std::max(r - (1ll << k) + 1, (1ll << k) - l + 1);
    }
    int k = safelg(r);
    return calc(l, (1ll << k) - (r - (1ll << k)) - 1) + (r - (1ll << k) + 1);
}
int main(){
    freopen("persecution.in","r",stdin);
    freopen("persecution.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        ll l,m;scanf("%lld%lld",&l,&m);
        ll r=l+m-1;
        printf("%lld\n",calc(l,r));
    }
}