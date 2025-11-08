#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
const int N=3e2+10,MOD=998244353;
int f[N+1][N+1][N+1];
int p[N],q[N];
int n;
int solve(int* p){
    static std::vector<int> res;
    res.resize(n);std::iota(ALL(res),1);
    struct seq{
        int a[3];
        bool ins(int v){
            for(int i=0;i<3;i++)
                if(a[i]<v){
                    a[i]=v;
                    return 1;
                }
            return 0;
        }
        int ans()const{
            if(std::lower_bound(ALL(res),a[2])!=res.begin()) return 0;
            return f[res.end()-std::upper_bound(ALL(res),a[0])]
            [std::lower_bound(ALL(res),a[0])-std::upper_bound(ALL(res),a[1])]
            [std::lower_bound(ALL(res),a[1])-std::upper_bound(ALL(res),a[2])];
        }
    };
    seq a{0,0,0};
    int ret=0;
    for(int i=1;i<n;i++){
        for(int j:res)if(j<p[i]){
            seq b=a;
            if(b.ins(j))
                (ret+=b.ans())%=MOD;
        }
        res.erase(std::find(ALL(res),p[i]));
        if(!a.ins(p[i])) break;
    }
    return ret;
}
int g[N][N][N],h[N][N][N];
void make(){
    f[0][0][0]=1;
    for(int s=0;s<=N;s++){
        for(int i=0;i<=N;i++){
            for(int j=std::max(s-i-N,0);s-i-j>=0&&j<=N;j++){
                int k=s-i-j;
                // for(int u=0;u<i;u++) if(i-u-1+j<=N)
                //     (f[i][j][k]+=f[u][i-u-1+j][k])%=MOD;
                // for(int v=0;v<j;v++) if(j-v-1+k<=N)
                //     (f[i][j][k]+=f[i][v][j-v-1+k])%=MOD;
                if(i) g[i][j][k]=(g[i-1][j+1][k]+f[i-1][j][k])%MOD;
                if(j) h[i][j][k]=(h[i][j-1][k+1]+f[i][j-1][k])%MOD;
                if(i|j|k) f[i][j][k]=(g[i][j][k]+h[i][j][k])%MOD;
                if(k) (f[i][j][k]+=f[i][j][k-1])%=MOD;
                printf("f[%d,%d,%d] = %d\n",i,j,k,f[i][j][k]);
            }
        }
    }
}
int main(){
    // freopen("ex_perm2.in","r",stdin);
    freopen(".out","w",stdout);
    make();
    int c,T;scanf("%d%d",&c,&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",p+i);
        for(int i=1;i<=n;i++) scanf("%d",q+i);
        int ans=MOD-solve(p);
        if(!std::next_permutation(q+1,q+n+1)) ans+=n<=3,std::reverse(q+1,q+n+1);
        (ans+=solve(q))%=MOD;
        printf("%d\n",ans);
    }
}