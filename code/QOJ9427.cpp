#include<bits/stdc++.h>
#define int long long
using std::cin;
using std::cout;
const int N=1e6+10;
int t[N],c[N];
struct range{
    int l,r;
    range(int l=1,int r=1e9):l(l),r(r){}
    bool in(int x){
        return l<=x&&x<=r;
    }
    range operator|(const range& b)const{
        return {std::min(l,b.l),std::max(r,b.r)};
    }
    void expand(int k){
        l=std::max(l-k,1ll),
        r=std::min(r+k,(int)1e9);
    }
};
int n;
bool check(int v){
    range r1,r2;
    t[0]=1;
    for(int i=1;i<=n;i++){
        r1.expand((t[i]-t[i-1])*v),r2.expand((t[i]-t[i-1])*v);
        if(!r1.in(c[i])&&!r2.in(c[i]))
            return 0;
        else if(r1.in(c[i])&&r2.in(c[i])){
            r2=r1|r2;
            r1={c[i],c[i]};
        }
        else if(r1.in(c[i])) r1={c[i],c[i]};
        else r2={c[i],c[i]};
    }
    return 1;
}
signed main(){
    // freopen64(".in","r",stdin);
    cin.tie(0),std::ios::sync_with_stdio(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>t[i]>>c[i];
        int left=0,right=1e9;
        while(left<right){
            int mid=(left+right)>>1;
            if(check(mid)) right=mid;
            else left=mid+1;
        }
        cout<<(left==1e9?-1:left)<<'\n';
    }
}