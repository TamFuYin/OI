#include<bits/stdc++.h>
const int N=1e5+10;
int a[2][N],f[N][2];
bool islas[2][N];
bool vis[N];
int main(){
    // freopen("ex_revealed6.in","r",stdin);
    // freopen("revealed.in","r",stdin);
    // freopen("revealed.out","w",stdout);
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a[0]+i);
    for(int i=1;i<=n;i++) scanf("%d",a[1]+i);
    for(int i=n;i>=1;i--){
        if(a[0][i]==a[1][i]){
            vis[a[0][i]]=1;
            continue;
        }
        if(!vis[a[0][i]]){
            vis[a[0][i]]=1;
            islas[0][i]=1;
        }
        if(!vis[a[1][i]]){
            vis[a[1][i]]=1;
            islas[1][i]=1;
        }
    }
    f[1][0]=islas[1][1];
    f[1][1]=a[0][1]!=a[1][1];
    for(int i=2;i<=n;i++){
        int w0=f[i-1][0]+(a[0][i-1]!=a[0][i]),
        w1=f[i-1][1]+(a[1][i-1]!=a[1][i]);
        f[i][0]=std::min(w0+islas[1][i],w1+(a[0][i]!=a[1][i]));
        f[i][1]=std::min(w1+islas[0][i],w0+(a[0][i]!=a[1][i]));
    }
    printf("%d",std::min(f[n][0],f[n][1]));
}