#include<bits/stdc++.h>
const int N=1e2,MOD=998244353;
int cnt[N];
int f[2][N][N*N/2];
int downpow(int n,int k){
    int ret=1;
    for(int i=n;i>=n-k+1;i--) ret=1ll*ret*i%MOD;
    return ret;
}
int main(){
    int n,x;scanf("%d%d",&n,&x);x=-x;
    for(int i=1,ai;i<=n;i++){
        scanf("%d",&ai);
        x+=ai;
        ++cnt[std::min(ai,n-1)];
        if(x>(n-1)*n/2){
            puts("0");
            return 0;
        }
    }
    if(x<=0){
        printf("%d",downpow(n,n));
        return 0;
    }
    f[n&1][0][0]=1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=n-i;j++){
            for(int k=0;k<=x;k++){
                f[i&1][j][k]=0;
                if(j) (f[i&1][j][k]+=f[i&1^1][j-1][k])%=MOD;
                for(int l=0;j+l<n-i&&k-l*i>=0&&l<=cnt[i];l++){
                    for(int t=0;k-(l+t)*i>=0&&l+t<=cnt[i];t++){
                        (f[i&1][j][k]+=1ll*f[i&1^1][j+l][k-(l+t)*i]*downpow(cnt[i],l+t)%MOD)%=MOD;
                    }
                }
            }
        }
    }
    int ret=0;
    for(int i=x;i<=(n-1)*n/2;i++) (ret+=f[0][0][i])%=MOD;
    printf("%d",ret);
}