#include<bits/stdc++.h>
const int MOD=998244353;
using ll=long long;
int qpow(int a,int b){
    int c=1;
    while(b){
        if(b&1) c=(ll)c*a%MOD;
        a=(ll)a*a%MOD;b>>=1;
    }
    return c;
}
std::vector<int> BM(const std::vector<int> &a){
    std::vector<int> f(0);
    int k=-114514,deltak;
    std::vector<int> fk(0);
    for(int i=0;i<a.size();i++){
        // printf("%d",i);
        int delta=a[i];
        for(int j=0;j<f.size();j++){
            (delta+=MOD-(ll)a[i-j-1]*f[j]%MOD)%=MOD;
        }
        if(delta==0) continue;
        std::vector<int> fi=f;
        if(k<0) for(int j=0;j<i;j++) f.push_back(0);
        else{
	        int rota=(ll)delta*qpow(deltak,MOD-2)%MOD;
	        if(f.size()<i-k+fk.size()) f.resize(i-k+fk.size());
	        (f[i-k-1]+=rota)%=MOD;
	        for(int j=0;j<fk.size();j++)
	            (f[i-k+j]+=MOD-(ll)rota*fk[j]%MOD)%=MOD;
        }
        if(fi.size()-i<fk.size()-k){
            fk=fi;
            k=i;
            deltak=delta;
        }
    }
    return f;
}
int main(){
    int n;scanf("%d",&n);
    std::vector<int> a(n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    std::vector<int> f=BM(a);
    for(int i:f) printf("%d ",i);
}
