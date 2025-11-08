#include<bits/stdc++.h>
double logbinom(int n,int k){
    return lgamma(n+1)-lgamma(k+1)-lgamma(n-k+1);
}
double logp(int n,int k){
    k=std::min(k,(2*n-1)/3);
    return logbinom(n,k)+k*log(2);
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,k;scanf("%d%d",&n,&k);
        if(k>=n) printf("%lf\n",log(3.0*k+1));
        else printf("%lf\n",log(3.0*k+1)+n*log(3)-logp(n,k));
    }
}