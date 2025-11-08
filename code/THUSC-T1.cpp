#include<cstdio>
const int D=1e5;
int n[D];
int tot[D];
using ull=unsigned long long;
int main(){
    int T,d;scanf("%d%d",&T,&d);
    while(T--){
        ull res=0;
        for(int i=1;i<=d;i++) scanf("%llu",&n[i]);
        int l,p;scanf("%d%d",&l,&p);int ans=p-l;
        for(int i=1;i<=d;i++) ans=n[i]%p*ans%p;
        for(int i=0;i<63;i++){
            for(int j=1;j<=d;j++){
                if(n[j]&1ull<<i){
                    (tot[j]+=1ull<<i%p)%=p;
                }
            }
            for(int j=1;j<=d;j++){
                if(n[j]&1ull<<i){
                    int cnt=1;
                    for(int k=1;k<=d;k++)
                    if(k!=j) cnt=1ll*cnt*tot[k]%p;
                    res&=~((1ull<<i+1)-1);
                    if(l>=res+(1ull<<i)-1){
                        (ans+=(1ull<<i)%p*l%p*cnt%p)%=p;
                    }
                    else if(l>=res){
                        for(int k=1;k<=i;k++){
                            
                        }
                    }
                    (ans+=(res+res+(1ull<<i)-1)%p*cnt%p*(1ull<<i)%p)%=p;
                }
            }
        }
    }
}