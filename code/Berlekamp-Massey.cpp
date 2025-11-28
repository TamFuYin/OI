#include<bits/stdc++.h>
const int MOD=998244353;
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%MOD;
        a=1ll*a*a%MOD;b>>=1;
    }
    return ret;
}
using poly=std::basic_string<int>;
poly BM(poly a){
    poly f,fl;int l=-1,dell;
    for(int i=0;i<a.size();i++){
        int del=a[i];
        for(int j=0;j<f.size();j++) (del+=MOD-1ll*a[i-j-1]*f[j]%MOD)%=MOD;
        if(del==0) continue;
        if(l==-1) f=poly(i+1,0),l=i,dell=del;
        else{
            poly g=poly(i-l-1,0)+(MOD-1)+fl;
            int k=MOD-1ll*del*qpow(dell,MOD-2)%MOD;
            if(g.size()>f.size()) fl=f,l=i,dell=del;
            f.resize(std::max(f.size(),g.size()));
            for(int i=0;i<g.size();i++) (f[i]+=1ll*k*g[i]%MOD)%=MOD;
        }
    }
    return f;
}
int main(){
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;std::cin>>n;poly a(n,0);
    for(int i=0;i<n;i++) std::cin>>a[i];
    poly f(BM(a));
    std::cout<<f.size()<<'\n';
    for(int i=0;i<f.size();i++) std::cout<<f[i]<<' ';
}