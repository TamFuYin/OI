#include<bits/stdc++.h>
const int V=16,N=1e7+10;
using ll=long long;
int sz[N];int pa[N];
ll pv[N],mod[V];
int findp(int x){
    if(pa[x]==x) return x;
    findp(pa[x]);
    pv[x]+=pv[pa[x]];
    if(x%V) pv[x]%=mod[x%V];
    return pa[x]=pa[pa[x]];
}
void merge(int x,int y,ll c=0){
    if(sz[x]<sz[y]) std::swap(x,y),c=-c;
    if(x%V) c=(c%mod[x%V]+mod[x%V])%mod[x%V];
    pa[y]=x;pv[y]=c;sz[x]+=sz[y];
}
int main(){
    // freopen("weight.in","r",stdin);
    // freopen("weight.out","w",stdout);
    for(int i=1;i<V;i++) mod[i]=1<<i;
    std::iota(pa,pa+N+1,0);
    std::fill(sz,sz+N+1,1);
    std::fill(pv,pv+N+1,0);
    int n,m;scanf("%d%d",&n,&m);
    while(m--){
        int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
        d=d==-1?0:std::__lg(d);
        for(int i=d!=0;i<=(d==0?V-1:d);i++){
            int x=a*V+i,y=b*V+i;
            if(findp(x)==findp(y)){
                ll t=pv[y]+c;
                if(i) t%=mod[i];
                if(t!=pv[x]){
                    puts("0");
                    goto Continue;
                }
            }
            else merge(pa[x],pa[y],pv[x]-pv[y]-c);
        }
        puts("1");
        Continue:;
    }
}