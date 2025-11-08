#include<bits/stdc++.h>
const int N=2e5+10;
char s[N];
int f[11][N];
std::pair<int,int> g[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m,k;scanf("%d%d%d",&n,&m,&k);k*=2;
        scanf("%s",s+1);
        for(int i=1;i<=n;i++) f[0][i]=s[i]=='A';
        for(int i=1;i<=m;i++) scanf("%d%d",&g[i].first,&g[i].second);
        for(int i=1;i<=k;i++){
            if(i&1) std::fill(f[i],f[i]+n+1,1);
            else std::fill(f[i],f[i]+n+1,0);
            for(int l=1;l<=m;l++){
                int u=g[l].first,v=g[l].second;
                if(i&1) f[i][v]&=f[i-1][u];
                else f[i][v]|=f[i-1][u];
            }
        }
        printf("%s\n",f[k][n]?"Alice":"Bob");
    }
}