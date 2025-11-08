#include<bits/stdc++.h>
const int N=1e6+10;
int pa[N],sz[N];
int findp(int x){
    if(pa[x]==x) return x;
    return pa[x]=findp(pa[x]);
}
void merge(int x,int y){
    x=findp(x),y=findp(y);
    if(sz[x]<sz[y]) std::swap(x,y);
    sz[x]+=sz[y];pa[y]=x;
}
using pii=std::pair<int,int>;
std::map<pii,int> et;
int n;
std::vector<pii> ie[N];
int main(){
    // freopen64(".in","r",stdin);
    // freopen64(".out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int m,q;scanf("%d%d%d",&n,&m,&q);
        std::fill(sz,sz+n,1);
        std::iota(pa,pa+n,0);
        et.clear();
        for(int i=1,u,v;i<=m;i++){
            scanf("%d%d",&u,&v);
            if(u>v) std::swap(u,v);
            et[{u,v}]=q+1;
        }
        int lu=0,lv=0;
        for(int i=1;i<=q;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            a=(a+lu)%n,
            b=(b+lv)%n;
            lu=(lu*2+1)%n;
            lv=(lv*3+1)%n;
            if(a>b) std::swap(a,b);
            if(et.find({a,b})!=et.end()&&et[{a,b}]==q+1) et[{a,b}]=i;
        }
        for(int i=1;i<=q+1;i++) ie[i].clear();
        for(auto p:et) ie[p.second].push_back(p.first);
        int ans=0;
        for(int i=q+1;i>=1;i--){
            for(auto p:ie[i]) merge(p.first,p.second);
            if(sz[findp(0)]==n) {ans=i-1;break;}
        }
        for(int i=1;i<=ans;i++) puts("1");
        for(int i=1;i<=q-ans;i++) puts("0");
    }
}