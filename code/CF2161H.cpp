#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
const int N=1e5;
int a[N],b[N];
using vi=std::vector<int>;
int x,y,d;
void solve(vi pa,vi pb,int L,int R){
    if(L==R){
        assert(pa.size()+pb.size()==1);
        if(pa.size()) a[pa[0]]=L;
        if(pb.size()) b[pb[0]]=L;
        return;
    }
    int x=L+R>>1;
    for(int i:pa) if(a[i]<=x)
}
int exgcd(int a,int b,int& x,int& y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;return d;
}
int main(){
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int T;std::cin>>T;
    while(T--){
        int n,m;std::cin>>n>>m;
        x,y,d=exgcd(n,m,x,y);
        for(int i=0;i<n;i++) std::cin>>a[i];
        for(int i=1;i<m;i++) std::cin>>b[i];
        vi pa(n),pb(m);
        std::iota(ALL(pa),1);
        std::iota(ALL(pb),1);
        solve(pa,pb,1,n+m);
    }
}