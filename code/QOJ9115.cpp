#include<bits/stdc++.h>
const int N=18;
int dp[N+1][1<<N][N+1];
int m;
void mul(int& x,int y){x=1ll*x*y%m;}
int main(){
    int n,k;scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<=n;i++)
        for(int j=0;j<(1<<n);j++)
            for(int l=0;l<=n;l++)
                dp[i][j][l]=1;
    for(int i=1;i<=k;i++){
        int c,d,x;scanf("%d%d%d",&c,&d,&x);
        mul(dp[0][c][d],x);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<n);j++){
            for(int k=0;k<=n;k++){
                mul(dp[i+1][j][k],dp[i][j][k]);
                mul(dp[i+1][j^1<<i][k-1],dp[i][j][k]);
            }
        }
    }
    for(int i=0;i<(1<<n);i++)
        printf("%d ",dp[n][i][0]);
}