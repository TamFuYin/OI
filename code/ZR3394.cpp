#include<bits/stdc++.h>
const int N=5e3+10,INF=1e9;
int a[N];
int s[N];
const int MOD=998244353;
struct pair{
    int v,c;
    pair operator+(const int x)const{
        return {v+x,c};
    }
}f[N][N];
pair min(pair a,pair b){
    if(a.v!=b.v) return a.v<b.v?a:b;
    return {a.v,(a.c+b.c)%MOD};
}
int main(){
    // freopen64("ex_knight5.in","r",stdin);
    // freopen64("ex_knight5.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int n,d;scanf("%d%d",&n,&d);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        auto big=[&](int x){return x>=(d+1)/2;};
        std::sort(a+1,a+n+1,[&](int x,int y){
            const bool tx=big(x),ty=big(y);
            if(tx&&ty) return x>y;
            if(!tx&&!ty) return x<y;
            if(tx&&!ty) return d-x<=y;
            if(!tx&&ty) return x<d-y;
            assert(0);
        });
        // for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
        const pair pairINF={INF,0};
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) f[i][j]=pairINF;
        f[0][0]={0,1};
        for(int i=1;i<=n;i++){
            s[i]=s[i-1]+big(a[i]);
            if(big(a[i]))
                for(int j=0;j<=i;j++) f[i][j]=min(f[i-1][j]+(s[i-1]-j),(j?f[i-1][j-1]:pairINF)+(j-1));
            else
                for(int j=0;j<=i;j++) f[i][j]=min(f[i-1][j]+(s[i-1]-j),f[i-1][j]+j);
        }
        pair ans={INF,0};
        for(int i=0;i<=n;i++) ans=min(ans,f[n][i]);
        printf("%d %d\n",ans.v,ans.c);
    }
}