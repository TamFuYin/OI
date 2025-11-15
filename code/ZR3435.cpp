#include<bits/stdc++.h>
const int N=2e6+10;
int a[N],aa[N],b[N];
const int MOD=998244353;
int fac[N+1],ifac[N+1];
int qpow(int n,int k){
    int r=1;
    while(k){
        if(k&1) r=1ll*r*n%MOD;
        n=1ll*n*n%MOD;k>>=1;
    }
    return r;
}
int binom(int n,int k){
    return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
using pii=std::pair<int,int>;
pii solve(int a[],int mid,int n){
    int cl=0,cr=0,c=0;
    for(int i=1;i<mid;i++){
        c+=a[i]>a[mid]?1:-1;
        if(c==0) ++cl;
    }
    int tmp=c!=0;
    for(int i=mid+1;i<=n;i++){
        c+=a[i]>a[mid]?1:-1;
        if(c==0) ++cr;
    }
    return {cl+cr,binom(cl+cr-tmp,cl)};
}
void ck(pii& a,pii b){
    if(b.first>a.first) a=b;
    else if(b.first==a.first) a.second+=b.second;
}
std::set<int> S;
int mid[N];
int al[N],ar[N],bl[N],br[N],cl[N],cr[N];
int main(){
    fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
    // freopen("meet5.in","r",stdin);
    // freopen("meet1.out","w",stdout);
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i),aa[a[i]]=i;
    if(n&1){
        int mid=std::find(a+1,a+n+1,(n+1)/2)-a;
        auto ans=solve(a,mid,n);
        printf("1 %d %d\n",ans.first,ans.second);
    }
    else{
        int l,r;S.insert(mid[1]=l=r=a[1]);
        for(int i=2;i<=n;i++){
            S.insert(a[i]);
            if(i&1) mid[i]=l=r=a[i]>r?r:(a[i]<l?l:a[i]);
            else{
                if(a[i]>l) r=*++S.find(l);
                else l=*--S.find(l);
                ++al[l+1];--al[r];
            }
        }
        S.clear();
        S.insert(mid[n]=l=r=a[n]);
        for(int i=n-1;i>=1;i--){
            S.insert(a[i]);
            if(i&1^1) mid[i]=l=r=a[i]>r?r:(a[i]<l?l:a[i]);
            else{
                if(a[i]>l) r=*++S.find(l);
                else l=*--S.find(l);
                ++ar[l+1];--ar[r];
            }
        }
        for(int i=1;i<=n;i++) al[i]+=al[i-1],ar[i]+=ar[i-1];
        for(int i=n;i>1;i-=2) ++br[mid[i]];
        for(int i=1;i<=n;i++) (i&1?cl[mid[i]]:cr[mid[i]])|=a[i]==mid[i];
        pii ans={0,0};
        for(int i=1;i<n;i++){
            if(i&1^1){
                --br[mid[i]];
                continue;
            }
            ++bl[mid[i]];
            int lm=mid[i],rm=mid[i+1],
            lf=al[lm]+bl[lm]-cl[lm],
            rf=ar[rm]+br[rm]-cr[rm],
            ls=binom(al[lm]+bl[lm]-1,al[lm]),
            rs=binom(ar[rm]+br[rm]-1,ar[rm]);
            ck(ans,{lf+rf,1ll*binom(lf+rf,lf)*ls%MOD*rs%MOD});
        }
        printf("2 %d %d\n",ans.first,ans.second);
    }
}