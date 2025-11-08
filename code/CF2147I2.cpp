#include<bits/stdc++.h>
using ll=long long;
std::set<ll> s;
int main(){
    freopen(".out","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    int p=0,q=3;
    for(int i=1;i<=n/4;i++){
        printf("%d %d %d %d ",p,1,q,0);
        assert(1-p<q-1);
        p-=4,q+=4;
    }
}
//100000 15000