#pragma GCC optimize(3)
#include<bits/stdc++.h>
const int N=5e4+10;
std::bitset<N> grp[N],pref[N],suf,bk[N];
int p[N];
using ll=long long;
ll ans;
int main(){
    // freopen(".in","r",stdin);
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",p+i),grp[p[i]-1].set(i);
    for(int i=n;i>=1;i--) grp[i]|=grp[i+1];
    for(int i=n;i>=1;i--) bk[i].set(i),bk[i]|=bk[i+1];
    if(m==1){
        for(int i=1;i<=n;i++) ans+=(grp[p[i]]&bk[i+1]).count();
        printf("%lld",ans);
        return 0;
    }
    for(int i=1;i<=n;i++){
        pref[i]=grp[p[i]];//prelen[i]=1;
        if(i%(m-1)!=1%(m-1)) pref[i]&=pref[i-1]<<1;//,prelen[i]=prelen[i-1]+1;
    }
    for(int i=n;i>=1;i--){
        if(i%(m-1)!=0) suf&=grp[p[i]]<<(m-1-i%(m-1))%(m-1);//,assert(i+m-1>n||suflen==(m-1-i%(m-1))%(m-1)),suflen++;
        else suf=grp[p[i]];//,suflen=1;
        // if(i+m-1<=n) assert(prelen[i+m-1]+suflen==m);
        if(i+m-1<=n) ans+=(suf<<(i-1)%(m-1)+1&pref[i+m-1]&bk[i+m]).count();
    }
    printf("%lld",ans);
}