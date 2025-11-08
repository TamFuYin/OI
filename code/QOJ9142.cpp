#include<bits/stdc++.h>
const int N=5e5+10;
int a[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        using ll=long long;
        int n;scanf("%d",&n);
        int max=0;ll sum=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),max=std::max(max,a[i]),sum+=a[i];
        printf("%lld\n",sum-max);
    }
}