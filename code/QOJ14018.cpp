#include<bits/stdc++.h>
const int N=5e5+10;
using ll=long long;
ll ans[N];
std::pair<int,int> a[N];
std::multimap<ll,std::vector<int> > Q;
struct VectorIntHash {
    // mixing helper (splitmix64)
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    std::size_t operator()(const std::vector<int>& v) const noexcept {
        // use a 64-bit accumulator for better distribution on 64-bit systems
        uint64_t acc = 14695981039346656037ULL; // FNV offset basis (just as seed)
        for (int x : v) {
            // mix each element into acc
            uint64_t k = static_cast<uint32_t>(x); // keep deterministic for negative values
            k = splitmix64(k);
            acc ^= k + 0x9e3779b97f4a7c15ULL + (acc << 6) + (acc >> 2); // boost mixing (like boost::hash_combine)
        }
        // finally mix length to avoid collisions between [1,2] and [1,2,0] etc.
        acc ^= splitmix64(v.size() + 0x9e3779b97f4a7c15ULL);

        return static_cast<std::size_t>(acc);
    }
};
std::unordered_map<std::vector<int>,ll,VectorIntHash> dis;
int main(){
    // freopen(".in","r",stdin);
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i].first),a[i].second=i;
    std::sort(a,a+n);
    dis[{n}]=(ll)n*a[0].first;
    Q[(ll)n*a[0].first]={n};
    int ans_cnt=0;
    while(!Q.empty()){
        ll disu=Q.begin()->first;
        auto b=Q.begin()->second;
        Q.erase(Q.begin());
        int x=0;
        for(int i=0;i<b.size();i++) (x+=1ll*b[i]*a[i].second%n)%=n;
        if(!ans[x]){
            ++ans_cnt,ans[x]=disu;
            if(ans_cnt==n) break;
        }
        for(int i=0;i<b.size();i++){
            if(b[i]){
                auto c=b;--c[i];
                if(i==b.size()-1) c.push_back(1);
                else ++c[i+1];
                ll disv=disu-a[i].first+a[i+1].first;
                auto it=dis.find(c);
                if(it==dis.end()||it->second>disv){
                    if(it!=dis.end()) Q.erase({it->second,it->first});
                    dis[c]=disv,
                    Q.emplace(disv,c);
                }
            }
        }
    }
    for(int i=0;i<n;i++) printf("%lld ",ans[i]);
}
