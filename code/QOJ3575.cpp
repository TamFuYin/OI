#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){a=std::min(a,b);}
const int N=3e5+10,lgN=31;
int a[N],b[N];
int f[N][lgN],g[N];
int solve(int n){
    for(int i=1;i<=n;i++){
        for(int j=0;j<lgN;j++) f[i][j]=0;
        f[i][__builtin_ctz(a[i])]=i+1,a[i]/=1<<__builtin_ctz(a[i]);
    }
    for(int j=0;j<lgN-1;j++)
        for(int i=1;i<=n;i++)
            if(f[i][j]&&f[i][j]<=n&&f[f[i][j]][j]&&a[i]==a[f[i][j]])
                f[i][j+1]=f[f[i][j]][j];
    std::fill(g+1,g+n+2,1e9);
    g[1]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<lgN;j++)
            if(f[i][j]) ckmin(g[f[i][j]],g[i]+1);
    return g[n+1];
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        for(int i=1;i<n;i++) b[i]=a[i+1]-a[i];
        --n;
        int ans=1;
        for(int i=1,las=1;i<=n+1;i++){
            if(b[i]==0||i==n+1){
                std::copy(b+las,b+i,a+1);
                ans+=solve(i-las);
                if(i!=n+1) ++ans;
                while(i<=n&&b[i]==0) ++i;
                las=i;
            }
        }
        printf("%d\n",ans);
    }
}