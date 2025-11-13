#include<bits/stdc++.h>
const int N=4e5+10;
int a[N],b[N],c[N];
int lsh[N],lcnt;
std::vector<int> vec[N*4];
void insert(int L,int R,int v,int l=0,int r=lcnt-1,int o=1){
    if(L<=l&&r<=R) return vec[o].push_back(v);
    int mid=l+r>>1;
    if(L<=mid) insert(L,R,v,l,mid,o<<1);
    if(R>mid) insert(L,R,v,mid+1,r,o<<1|1);
}
std::vector<int> to[N];
int tag[N],ans[N];
int pa[N],sz[N];
std::stack<std::pair<int*,int>> tst;
std::stack<std::pair<int,int>> tstm;
void mark(int& x){
    tst.push({&x,x});
}
int findp(int x){
    mark(pa[x]);
    return x==pa[x]?x:pa[x]=findp(pa[x]);
}
template<typename T>void ckmax(T&a,T b){
    if(a<b) a=b;
}
void merge(int i,int j){
    i=findp(i),j=findp(j);
    if(i==j) return;
    if(sz[i]<sz[j]) std::swap(i,j);
    mark(pa[j]),mark(sz[i]);
    pa[j]=i,sz[i]+=sz[j];
    ckmax(a[i],a[j]);
    tstm.push({i,j});
}
void split(int i,int j){
    ckmax(a[i],a[findp(i)]),
    ckmax(a[j],a[findp(i)]);
}
bool avail[N],vis[N];
void segDC(int l=0,int r=lcnt-1,int o=1){
    int t1=tst.size(),t2=tstm.size();
    for(int i:vec[o]) avail[i]=vis[i]=1;
    for(int i:vec[o])
        for(int j:to[i])
            if(avail[j]) merge(i,j);
            else if(vis[j]) ckmax(a[i],a[findp(j)]);
    for(int i:vec[o]) ckmax(a[findp(i)],a[i]);
    if(l!=r){
        int mid=l+r>>1;
        segDC(mid+1,r,o<<1|1);
        segDC(l,mid,o<<1);
    }
    while(tstm.size()>t2)
        split(tstm.top().first,tstm.top().second),
        tstm.pop();
    while(tst.size()>t1)
        *tst.top().first=tst.top().second,
        tst.pop();
    for(int i:vec[o]) avail[i]=0;
}
int main(){
    // freopen("ex_nobye3.in","r",stdin);
    // freopen("ex_nobye3.out","w",stdout);
    int type,n,m;scanf("%d%d%d",&type,&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d%d",a+i,b+i,c+i),
    lsh[lcnt++]=b[i],lsh[lcnt++]=c[i];
    std::sort(lsh,lsh+lcnt);
    lcnt=std::unique(lsh,lsh+lcnt)-lsh;
    for(int i=1;i<=n;i++){
        b[i]=std::lower_bound(lsh,lsh+lcnt,b[i])-lsh;
        c[i]=std::lower_bound(lsh,lsh+lcnt,c[i])-lsh;
        insert(b[i],c[i],i);
    }
    for(int i=1,u,v;i<=m;i++)
        scanf("%d%d",&u,&v),to[u].push_back(v),to[v].push_back(u);
    std::iota(pa+1,pa+n+1,1);
    std::fill(sz+1,sz+n+1,1);
    segDC();
    if(type==0) printf("%d ",a[findp(1)]);
    else for(int i=1;i<=n;i++) printf("%d ",a[findp(i)]);
}