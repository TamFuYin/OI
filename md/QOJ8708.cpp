#include<bits/stdc++.h>
const int N=1e5;
int x[N],y[N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i);
    std::sort(x+1,x+n+1),std::sort(y+1,y+n+1);
    int gx=0,gy=0;
    for(int i=2;i<=n;i++)
        gx=std::__gcd(gx,x[i]-x[i-1]),
        gy=std::__gcd(gy,y[i]-y[i-1]);
    printf("%lld\n",1ll*gx*gy);
}