#include<bits/stdc++.h>
const int N=1e5,M=22;
std::pair<int,int> b[N];
int n,t[N*4],tag[N*4];
void pushdown(int o){
    if(tag[o]!=1){
        t[o<<1]*=tag[o];
        tag[o<<1]*=tag[o];
        t[o<<1|1]*=tag[o];
        tag[o<<1|1]*=tag[o];
        tag[o]=1;
    }
}
void pushup(int o){t[o]=t[o<<1]+t[o<<1|1];}
int getsum(int L,int R,int l=0,int r=n,int o=1){
    if(L<=l&&r<=R) return t[o];
    int mid=l+r>>1,ret=0;
    pushdown(o);
    if(L<=mid) ret+=getsum(L,R,l,mid,o<<1);
    if(mid<R) ret+=getsum(L,R,mid+1,r,o<<1|1);
    return ret;
}
void times(int L,int R,int l=0,int r=n,int o=1){
    if(L<=l&&r<=R) {t[o]*=2;tag[o]*=2;return;}
    int mid=l+r>>1;
    pushdown(o);
    if(L<=mid) times(L,R,l,mid,o<<1);
    if(mid<R) times(L,R,mid+1,r,o<<1|1);
    pushup(o);
}
int f[N];
void build(int l=0,int r=n,int o=1){
    if(l==r) {t[o]=f[l];tag[o]=1;return;}
    int mid=l+r>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
    t[o]=t[o<<1]+t[o<<1|1];
    tag[o]=1;
}
namespace BIT{
    
}
int stir2[M][M],fact[M];
int main(){
    int m;scanf("%d%d",&n,&m);
    for(int i=0;i<=m;i++){
        stir2[i][0]=i==0;
        for(int j=1;j<=i;j++){
            stir2[i][j]=stir2[i-1][j-1]+j*stir2[i-1][j];
        }
    }
    fact[0]=1;
    for(int i=1;i<=m;i++) fact[i]=fact[i-1]*i;
    for(int i=1;i<=n;i++) scanf("%d",&b[i].first),b[i].second=i;
    std::sort(b+1,b+n+1);
    f[0]=1;
    int ans=0;
    for(int j=1;j<=m;j++){
        build();
        memset(f,0,sizeof f);
        for(int k=1;k<=n;k++){
            int i=b[k].second;
            f[i]=getsum(0,i-1);
            times(0,i-1);
            printf("f[%d]=%d\n",i,f[i]);
        }
        puts("");
        for(int i=1;i<=n;i++){
            ans+=fact[j]*stir2[m][j]*f[i];
        }
    }
    printf("%d",ans);
}
