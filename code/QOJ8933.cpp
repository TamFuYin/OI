#include<bits/stdc++.h>
const int N=1e2;
bool f[N][N][N];
int main(){
    freopen64("ex_1.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        memset(f,0,sizeof f);
        f[0][0][0]=1;
        int cnt=0;
        for(int i=1;i<=n;i++){
            char t[3];scanf("%s",t);
            if(t[0]=='B'){
                ++cnt;
                for(int j=0;j<=n;j++){
                    for(int k=0;k<=n;k++){
                        if(k<n) f[i][j][k]|=f[i-1][j][k+1];
                        if(j) f[i][j][k]|=f[i-1][j-1][k];
                    }
                }
            }
            else{
                int a,b;scanf("%d%d",&a,&b);
                for(int j=0;j<=n;j++){
                    for(int k=0;k<=n;k++){
                        if(j+a<=n) f[i][j][k]|=f[i-1][j+a][k];
                        if(k>=b) f[i][j][k]|=f[i-1][j][k-b];
                    }
                }
            }
        }
        int ans=INT_MAX;
        for(int i=0;i<=cnt;i++) if(f[n][i][0]) {ans=i;break;}
        printf("%d\n",cnt*2-ans);
    }
}