/*
link: https://codeforces.com/contest/2147/problem/H
*/
#include<bits/stdc++.h>
const int N=51,M=N*N;
namespace flow{
    int nx[M],ls[N],to[M],ca[M],fl[M],tot,n;
    void clear(int _n){
        n=_n;std::fill(ls+1,ls+n+1,0),tot=1;
    }
    void clear_fl(){
        for(int i=2;i<=tot;i++) fl[i]=0;
    }
    void add_half(int u,int v,int w){
        // assert(u<=n&&v<=n);
        nx[++tot]=ls[u];
        to[ls[u]=tot]=v;
        ca[tot]=w;fl[tot]=0;
    }
    int dep[N],cur[N];
    bool bfs(int s,int t){
        static std::queue<int> q;
        std::fill(dep+1,dep+n+1,0);
        std::copy(ls+1,ls+n+1,cur+1);
        q.push(s);dep[s]=1;
        // puts("(");
        while(!q.empty()){
            int u=q.front();q.pop();
            // printf(">>> %d\n",u);
            if(u==t) continue;
            for(int i=ls[u],v;i;i=nx[i]){
                // printf("%d\n",i);
                if(!dep[v=to[i]]&&fl[i]<ca[i])
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        // puts(")");
        return dep[t];
    }
    int dfs(int u,int t,int flow=INT_MAX){
        if(u==t) return flow;
        int ret=0;
        for(int& i=cur[u],v;i&&flow;i=nx[i])
        if(dep[v=to[i]]==dep[u]+1){
            int f=dfs(v,t,std::min(flow,ca[i]-fl[i]));
            fl[i]+=f,fl[i^1]-=f,flow-=f,ret+=f;
        }
        return ret;
    }
    int dinic(int s,int t){
        int ret=0;
        while(bfs(s,t)) ret+=dfs(s,t);
        return ret;
    }
    int* cut(int* begin,int* end){
        static bool vis[N];
        static int tmp[2][N];
        std::fill(vis+1,vis+n+1,0);
        static std::queue<int> q;
        int s=*begin;
        q.push(s);vis[s]=1;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=ls[u],v;i;i=nx[i])
                if(!vis[v=to[i]]&&fl[i]<ca[i])
                    q.push(v),vis[v]=1;
        }
        int cnt[2]={0,0};
        for(int* i=begin;i!=end;++i)
            tmp[vis[*i]][cnt[vis[*i]]++]=*i;
        for(int i=0;i<cnt[1];i++) *(begin+i)=tmp[1][i];
        for(int i=0;i<cnt[0];i++) *(begin+cnt[1]+i)=tmp[0][i];
        return begin+cnt[1];
    }
}
int d;
int p[N];
void GHT(int* begin,int* end){
    using namespace flow;
    if(end-begin==1) return;
    clear_fl();
    d=std::__gcd(d,dinic(*begin,*(begin+1)));
    int* mid=cut(begin,end);
    GHT(begin,mid),GHT(mid,end);
}
bool col[N];
bool solve(bool A[N][N], bool b[], bool x[], int n) {
    std::vector<std::vector<bool>> mat(n, std::vector<bool>(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = A[i][j];
        }
        mat[i][n] = b[i];
    }
    int rank = 0;
    std::vector<int> pivot_cols(n, -1);
    for (int col = 0; col < n && rank < n; ++col) {
        int pivot_row = rank;
        while (pivot_row < n && !mat[pivot_row][col]) {
            pivot_row++;
        }
        if (pivot_row < n) {
            std::swap(mat[rank], mat[pivot_row]);
            pivot_cols[rank] = col;
            for (int i = 0; i < n; ++i) {
                if (i != rank && mat[i][col]) {
                    for (int j = col; j <= n; ++j) {
                        mat[i][j] = mat[i][j] ^ mat[rank][j];
                    }
                }
            }
            rank++;
        }
    }
    for (int i = rank; i < n; ++i) {
        if (mat[i][n]) {
            return false;
        }
    }
    std::fill(x, x + n, false);
    for (int i = rank - 1; i >= 0; --i) {
        int pivot_col = pivot_cols[i];
        bool val = mat[i][n];
        for (int j = i + 1; j < rank; ++j) {
            int current_col = pivot_cols[j];
            if (mat[i][current_col]) {
                val = val ^ x[current_col];
            }
        }
        x[pivot_col] = val;
    }
    return true;
}
bool L[N][N],deg[N],x[N];
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        flow::clear(n);
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) L[i][j]=0;
        for(int i=0;i<n;i++) deg[i]=0;
        for(int i=1;i<=m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);
            flow::add_half(u,v,w);
            flow::add_half(v,u,w);
            --u,--v;
            if(w&1) L[u][v]=L[v][u]=1,deg[u]^=1,deg[v]^=1;
        }
        for(int i=0;i<n;i++) L[i][i]=deg[i];
        std::iota(p+1,p+n+1,1);
        d=0;GHT(p+1,p+n+1);
        if(d!=1){
            printf("1\n%d\n",n);
            for(int i=1;i<=n;i++) printf("%d ",i);puts("");
        }
        else{
            assert(solve(L,deg,x,n));
            printf("2\n");
            std::vector<int> c0(0),c1(0);
            for(int i=0;i<n;i++) (x[i]?c1:c0).push_back(i+1);
            assert(c0.size()&&c1.size());
            printf("%d\n",(int)c0.size());
            for(int i:c0) printf("%d ",i);puts("");
            printf("%d\n",(int)c1.size());
            for(int i:c1) printf("%d ",i);puts("");
        }
    }
}