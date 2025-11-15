#include<bits/stdc++.h>
const int N=1e5+10;
int a[N];
std::map<int,int> S;
bool b[N];
int ans;
int n,mx;
auto getRange(int i){
    assert(i!=mx);
    return i<mx?std::make_pair(i,i+(n-a[i]+1)-1):std::make_pair(i-(n-a[i]+1)+1,i);
}
bool Contain(std::pair<int,int> r1,std::pair<int,int> r2){
    return r1.first<=r2.first&&r1.second>=r2.second;
}
bool mxcheck(int x){
    return Contain(getRange(x),{mx,mx+(n-a[mx]+1)-1})||Contain(getRange(x),{mx-(n-a[mx]+1)+1,mx});
}
bool check(int x,int y){
    return y==mx?mxcheck(x):Contain(getRange(x),getRange(y));
}
void erase(int x){
    auto it=S.find(a[x]),nx=std::next(it);
    if(mx==x){
        if(it==S.begin()) mx=0;
        else mx=std::prev(it)->second;
    }
    if(nx!=S.end()) ans-=!b[x];
    if(it!=S.begin()){
        auto pr=std::prev(it);
        ans-=!b[pr->second];
        if(nx!=S.end()) b[pr->second]=check(pr->second,nx->second),ans+=!b[pr->second];
        else if(pr!=S.begin()){
            auto ppr=std::prev(pr);
            assert(mx==pr->second);
            ans-=!b[ppr->second];
            b[ppr->second]=mxcheck(ppr->second);
            ans+=!b[ppr->second];
        }
    }
    S.erase(it);
}
void insert(int x,int y){
    a[x]=y;
    if(!mx||a[mx]<y) mx=x;
    auto nx=S.upper_bound(y);
    if(nx!=S.end()&&nx!=S.begin()) ans-=!b[std::prev(nx)->second];
    if(nx!=S.end()) b[x]=check(x,nx->second),ans+=!b[x];
    if(nx!=S.begin()){
        auto pr=std::prev(nx);
        ans-=!b[pr->second];
        b[pr->second]=check(pr->second,x);
        ans+=!b[pr->second];
    }
    S.emplace(y,x);
}
int main(){
    freopen64(".in","r",stdin);
    int q;scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        if(a[i]) insert(i,a[i]);
    }
    puts(!ans?"YES":"NO");
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        if(a[x]) erase(x);
        if(y) insert(x,y);
        puts(!ans?"YES":"NO");
    }
}