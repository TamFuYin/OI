#include<bits/stdc++.h>
const int N=4e3+10;
int co[N],n;
int al[N],ar[N];
const int INF=1e9;
const int M=N*3;
int nx[M],to[M],va[M],ls[N],tot;
void add(int u,int v,int w){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
    va[tot]=w;
}
bool spfa(int n,int s){
    static int dis[N],cnt[N];
    static bool inq[N];
    std::fill(dis,dis+n,INF);
    std::fill(cnt,cnt+n,0);
    std::fill(inq,inq+n,0);
    std::queue<int> q;
    q.push(s),dis[s]=0,inq[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop(),inq[u]=0;
        for(int i=ls[u];i;i=nx[i]){
            int v=to[i],w=va[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!inq[v]){
                    inq[v]=1;
                    if(++cnt[v]>n) return 0;
                    q.push(v);
                }
            }
        }
    }
    return 1;
}
const int MOD=998244353;
int inv[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        n=0;
        for(int i=1;i<=m;i++)
            scanf("%d%d",al+i,ar+i),--al[i],
            co[n++]=al[i],co[n++]=ar[i];
        std::sort(co,co+n);
        n=std::unique(co,co+n)-co;
        for(int i=1;i<=m;i++)
            al[i]=std::lower_bound(co,co+n,al[i])-co,
            ar[i]=std::lower_bound(co,co+n,ar[i])-co;
        std::pair<double,int> ans(INFINITY,-1);
        inv[1]=1;
        for(int i=2;i<=n;i++) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
        for(int min=1;min<=n;min++){
            int left=min,right=INF;
            while(left<right){
                int mid=left+right>>1;
                std::fill(ls,ls+n,0),tot=0;
                for(int i=1;i<n;i++) add(i,i-1,0);
                for(int i=1;i<=m;i++) add(ar[i],al[i],-min),add(al[i],ar[i],mid);
                if(spfa(n,n-1)) right=mid;
                else left=mid+1;
            }
            ans=std::min(ans,std::make_pair(1.*left/min,int(1ll*left*inv[min]%MOD)));
        }
        printf("%d\n",ans.second);
    }
}