#include<bits/stdc++.h>
const int N=71;
int s[N],f[N][N][N][N];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&s[i]);
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=1;k<=m;k++){
                for(int i=0;i<=20;i++){
                    f[l][r][k][i]+=f[l][r][k-1][i];
                    for(int p=l;p<=r;p++){
                        f[l][r][k][i]+=f[l][p-1][k-1][s[p]]*f[p+1][r][k][i];
                    }
                }
            }
        }
    }
    printf("%d",f[1][n][m][0]);
}

