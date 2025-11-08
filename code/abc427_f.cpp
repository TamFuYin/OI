#include<bits/stdc++.h>
int m,n;
int modm(int x){return x>=m?x-m:x;}
std::unordered_map<int,int> mp;
const int N=61;
int a[N],goal;
using ll=long long;
void dfs1(int i,int s){
    if(i==0){
        ++mp[s];
        return;
    }
    s=modm(s+a[i]);
    for(int j=std::max(i-2,0);j>=0;j--) dfs1(j,s);
}
ll ans;
int xs=1;
void dfs2(int i,int s){
    if(i==n+1){
        ans+=mp[modm(goal+m-s)]*xs;
        return;
    }
    s=modm(s+a[i]);
    for(int j=std::min(i+2,n+1);j<=n+1;j++) dfs2(j,s);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);goal=0;
    ++mp[0];
    for(int i=1;i<=n/2;i++) dfs1(i,0);
    ans+=mp[0];
    for(int i=n/2+1;i<=n;i++) dfs2(i,0);
    mp.clear();
    if(n!=1){
        dfs1(n/2,0);
        xs=-1;dfs2(n/2+1,0);
    }
    printf("%lld",ans);
}