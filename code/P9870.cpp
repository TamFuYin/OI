#include<bits/stdc++.h>
const int N=5e5+10;
int x[N],y[N],n,m;
using pii=std::pair<int,int>;
struct pair{
    pii min,max;
    pair():min({INT_MAX,0}),max({INT_MIN,0}){}
    void ck(pii b){
        min=std::min(min,b);
        max=std::max(max,b);
    }
};
pair px[N],py[N],sx[N],sy[N];
bool p2e(int u,int v){//point to edge
    if(!u||!v) return 1;
    if(px[u].min.first<py[v].min.first) return p2e(u,py[v].min.second-1);
    if(px[u].max.first<py[v].max.first) return p2e(px[u].max.second-1,v);
    return 0;
}
bool e2p(int u,int v){//edge to point
    if(u>n||v>m) return 1;
    if(sx[u].min.first<sy[v].min.first) return e2p(u,sy[v].min.second+1);
    if(sx[u].max.first<sy[v].max.first) return e2p(sx[u].max.second+1,v);
    return 0;
}
bool swaped;
bool p2p(){//point to point
    if(x[1]>=y[1]) std::swap(x,y),std::swap(n,m),swaped=1;
    if(x[n]>=y[m]) return 0;
    if(n==1&&m==1) return 1;
    for(int i=1;i<=n;i++) (px[i]=px[i-1]).ck({x[i],i});
    for(int i=1;i<=m;i++) (py[i]=py[i-1]).ck({y[i],i});
    for(int i=n;i>=1;i--) (sx[i]=sx[i+1]).ck({x[i],i});
    for(int i=m;i>=1;i--) (sy[i]=sy[i+1]).ck({y[i],i});
    if(sx[1].min.first>=sy[1].min.first||sx[1].max.first>=sy[1].max.first) return 0;
    return p2e(sx[1].min.second-1,sy[1].max.second-1)&&e2p(sx[1].min.second+1,sy[1].max.second+1);
}
int tx[N],ty[N];
int main(){
    // freopen("P9870_1.in","r",stdin);
    int c,q;scanf("%d%d%d%d",&c,&n,&m,&q);
    for(int i=1;i<=n;i++) scanf("%d",x+i);
    for(int i=1;i<=m;i++) scanf("%d",y+i);
    std::copy(x+1,x+n+1,tx+1);
    std::copy(y+1,y+m+1,ty+1);
    putchar('0'+p2p());
    if(swaped) std::swap(n,m),swaped=0;
    std::copy(tx+1,tx+n+1,x+1);
    std::copy(ty+1,ty+m+1,y+1);
    while(q--){
        std::copy(x+1,x+n+1,tx+1);
        std::copy(y+1,y+m+1,ty+1);
        int kx,ky;scanf("%d%d",&kx,&ky);
        while(kx--){
            int p,v;scanf("%d%d",&p,&v);
            x[p]=v;
        }
        while(ky--){
            int p,v;scanf("%d%d",&p,&v);
            y[p]=v;
        }
        putchar('0'+p2p());
        if(swaped) std::swap(n,m),swaped=0;
        std::copy(tx+1,tx+n+1,x+1);
        std::copy(ty+1,ty+m+1,y+1);
    }
}