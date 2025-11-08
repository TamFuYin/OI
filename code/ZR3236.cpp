#include<bits/stdc++.h>
void ckmin(int& a,int b){if(b<a) a=b;}
void ckmax(int& a,int b){if(b>a) a=b;}
const int N=2e5+10;
int a[N];
int c[N];
int s[N];
int l[N],r[N];
int m=2e5;
int f[N],g[N];
std::vector<int> range[N];
int main(){
    // freopen64(".in","r",stdin);
    // freopen64("ex_divination2.in","r",stdin);
    // freopen64("ex_divination2.out","w",stdout);
    int T,C;scanf("%d%d",&T,&C);
    while(T--){
        int n;scanf("%d",&n);
        std::fill(l+1,l+m+1,INT_MAX);
        std::fill(r+1,r+m+1,INT_MIN);
        std::fill(c+1,c+m+1,0);
        for(int i=1;i<=n;i++) scanf("%d",a+i),
        ckmin(l[a[i]],i),ckmax(r[a[i]],i);
        s[n+1]=0;
        for(int i=n;i>=1;i--) s[i]=++c[a[i]];
        for(int i=1;i<=n;i++) range[i].clear();
        g[0]=n;
        for(int i=1;i<=m;i++) if(c[i]) range[r[i]].push_back(i);
        int ans=INT_MAX;
        for(int i=1;i<=n;i++){
            f[i]=INT_MAX;
            for(int j:range[i]) ckmin(f[i],g[l[j]-1]-c[j]);
            g[i]=std::min(g[i-1],f[i]);
            ckmin(ans,g[i]-s[i+1]);
        }
        printf("%d\n",ans);
    }
}