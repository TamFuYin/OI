#include<bits/stdc++.h>
const char t[]="shwy";
int bh(char c){
    return std::find(t,t+4,c)-t;
}
using ll=long long;
const int N=1e5+10;
const ll MOD=1e18+3;
std::string s;
constexpr int M=2e7+7;
struct hashmap{
    std::vector<int> lis;
    int a[M];ll b[M];
    hashmap(){
        memset(a,0,sizeof a);
        memset(b,-1,sizeof b);
    }
    void clear(){
        for(int i:lis) a[i]=0,b[i]=-1;
        lis.clear();
    }
    int& operator[](ll x){
        int i=x%M;
        while(b[i]!=-1&&b[i]!=x) i=(i+1)%M;
        if(b[i]!=x) b[i]=x,lis.push_back(i);
        return a[i];
    }
}cnt;
int cur[4];
void clear(){
    cnt.clear();
    memset(cur,0,sizeof cur);
}
ll ya(){
    int t=cur[0]/2;
    for(int i=1;i<4;i++) t=std::min(t,cur[i]);
    ll ret=cur[0]-t*2;
    for(int i=1;i<4;i++) ret=((__int128)ret*N%MOD+(cur[i]-t))%MOD;
    return ret;
}
int main(){
    freopen("sshwy.in","r",stdin);
    freopen("sshwy.out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int T;std::cin>>T;
    while(T--){
        std::cin>>s;
        // std::cout<<s<<'\n';
        int n=s.length();
        ll ans=0;
        clear();
        ++cnt[0];
        for(int i=0;i<n;i++){
            if(bh(s[i])==4){
                clear();
                ++cnt[0];
                while(i+1<n&&bh(s[i+1])==4) ++i;
                continue;
            }
            ++cur[bh(s[i])];
            ll k=ya();
            ans+=cnt[k];
            ++cnt[k];
        }
        std::cout<<ans<<'\n';
    }
}