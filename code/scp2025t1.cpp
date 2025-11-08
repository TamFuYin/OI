#include<bits/stdc++.h>
const int N=1e6+10;
int s[N];
std::map<int,int> mp;
template<typename T>void ckmax(T &x,T y){if(x<y)x=y;}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        mp.clear();mp[0]=1;s[0]=0;
        for(int i=1,a;i<=n;i++) scanf("%d",&a),s[i]=s[i-1]+a,mp[s[i]]++;
        int ans=0;
        for(auto p:mp) ckmax(ans,p.second);
        printf("%d\n",ans-1);
    }
}