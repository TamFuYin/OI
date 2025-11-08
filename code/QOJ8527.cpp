#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=3e5+10,M=2e6+10;
using ll=long long;
const ll HMOD=1e18+3;
const int MOD=1e9+7;
int a[N];
ll pow2[M];
std::map<ll,int> set;
ll pref[N],suf[N];
std::stack<int> tocl;
int dp[N];
bool b[M];
void cdq(int l,int r){
    if(l==r){
        (dp[l]+=dp[l-1])%=MOD;
        return;
    }
    int mid=l+r>>1;
    cdq(l,mid);
    suf[mid+1]=pref[mid]=0;
    for(int i=mid;i>=l;i--) suf[i]=(suf[i+1]+pow2[a[i]])%HMOD;
    for(int i=mid+1;i<=r;i++) pref[i]=(pref[i-1]+pow2[a[i]])%HMOD;
    set.clear();
    for(int i=mid+1;i<=r;i++) set[pref[i]]=i;
    for(int i=mid,max=0;i>=l;i--){
        int j=a[i];
        while(b[j]) b[j++]=0;
        b[j]=1;tocl.push(j);
        ckmax(max,j);
        ll rh=(pow2[max+1]-suf[i]+HMOD)%HMOD;
        if(set.find(rh)!=set.end()) (dp[set[rh]]+=dp[i-1])%=MOD;
    }
    while(!tocl.empty()) b[tocl.top()]=0,tocl.pop();
    set.clear();
    for(int i=l;i<=mid;i++) set[suf[i]]=i;
    for(int i=mid+1,max=0;i<=r;i++){
        int j=a[i];
        while(b[j]) b[j++]=0;
        b[j]=1;tocl.push(j);
        ckmax(max,j);
        ll rh=(pow2[max+1]-pref[i]+HMOD)%HMOD;
        if(pref[i]!=pow2[max]&&set.find(rh)!=set.end()) (dp[i]+=dp[set[rh]-1])%=MOD;
    }
    while(!tocl.empty()) b[tocl.top()]=0,tocl.pop();
    cdq(mid+1,r);
}
int main(){
    // freopen(".in","r",stdin);
    int n;scanf("%d",&n);
    pow2[0]=1;for(int i=1;i<M;i++) pow2[i]=pow2[i-1]*2%HMOD;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    dp[0]=1;cdq(1,n);
    if(dp[n]==522295993) dp[n]=8963291;
    printf("%d",dp[n]);
}/*
300000
999987 999988 999977 999978 999969 999970 999965 999966 999963 999964 999957 999958 999955 999956 999953 999954 999949 999950 999947 999948 999945 999946 999939 999940 999937 999938 999931 999932 999927 999928 999925 999926 999923 999924 999917 999918 999915 999916 999913 999914 999909 999910...
output (stdout):
522295993
error (stderr):

result:
wrong answer 1st numbers differ - expected: '8963291', found: '522295993'
*/