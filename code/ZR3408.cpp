#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){
    a=std::min(a,b);
}
template<typename T>
void ckmax(T& a,T b){
    a=std::max(a,b);
}
const int N=5e5+10;
int a[N];
std::vector<int> to[N];
int siz[N],dfn[N],rnk[N],dfncnt;
void dfs(int u){
    siz[u]=1;rnk[dfn[u]=++dfncnt]=u;
    for(int v:to[u]) dfs(v),siz[u]+=siz[v];
}
int pref[N],suff[N];
int s[N],s2[N];
int main(){
    freopen("persistent.in","r",stdin);
    freopen("persistent.out","w",stdout);
    // freopen(".in","r",stdin);
    int n,k;scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=2,p;i<=n;i++) scanf("%d",&p),to[p].push_back(i);
    dfs(1);
    for(int i=1;i<=n;i++) s[i]=s[i-1]^a[rnk[i]];
    for(int i=1;i<=n;i++) s2[i]=s2[i-1]^std::min(a[rnk[i]],k);
    auto get=[](int l,int r){return l<=r?s[r]^s[l-1]:0;};
    auto get2=[](int l,int r){return l<=r?s2[r]^s2[l-1]:0;};
    int q;scanf("%d",&q);
    pref[0]=0,suff[0]=n+1;
    for(int i=1;i<=q;i++){
        int op,x;scanf("%d%d",&op,&x);
        pref[i]=pref[i-1],suff[i]=suff[i-1];
        int l=dfn[x],r=dfn[x]+siz[x]-1;
        if(op==1) ckmax(pref[i],l-1),ckmin(suff[i],r+1);
        else if(op==2){
            if(r<=pref[i]||l>=suff[i]||pref[i]+1>=suff[i]) printf("%d\n",get2(l,r));
            else{
                int L=std::max(pref[i]+1,l),R=std::min(suff[i]-1,r);
                printf("%d\n",get2(l,L-1)^get(L,R)^get2(R+1,r));
            }
        }
        else pref[i]=pref[x-1],suff[i]=suff[x-1];
    }
}