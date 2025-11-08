#include<bits/stdc++.h>
template<typename T>void ckmin(T &a,T b){if(b<a)a=b;}
const int N=1e6+10,Σ=26;
char s[N],t[N];
int a[Σ][Σ];
int to[Σ],ind[Σ];
bool vis[Σ];
bool ht[Σ];
std::vector<int> ce[Σ];
int g[Σ][Σ];
int dp[1<<Σ/2];
bool onc[Σ];
int main(){
    freopen(".in","r",stdin);
    // freopen("ex_edit4.in","r",stdin);
    // freopen("ex_edit4.out","w",stdout);
    int n,k;scanf("%d%d%s%s",&n,&k,s,t);
    for(int i=0;i<n;i++) a[s[i]-'a'][t[i]-'a']++;
    // printf("%d\n",std::min(a[0][1]+a[1][0],k+std::min(a[0][0]+a[1][0],a[0][1]+a[1][1])));
    int ans=n;
    for(int i=0;i<Σ;i++){
        int p=std::max_element(a[i],a[i]+Σ)-a[i];
        if(k-a[i][p]<-a[i][i]) to[i]=p,ans+=k-a[i][p];
        else to[i]=i,ans+=-a[i][i];
    }
    for(int i=0;i<Σ;i++) ++ind[to[i]];
    std::queue<int> q;
    for(int i=0;i<Σ;i++) if(ind[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();ht[to[u]]=1;
        if(!--ind[to[u]]) q.push(to[u]);
    }
    int c=0;
    for(int i=0;i<Σ;i++) if(ind[i]&&!vis[i]&&to[i]!=i){
        int u=i,iht=0;std::vector<int> tmp;assert(tmp.empty());
        do vis[u]=1,iht|=ht[u],tmp.push_back(u),u=to[u];while(u!=i);
        if(!iht) ce[c++]=tmp;
    }
    for(int i=0;i<c;i++) for(int j:ce[i]) onc[j]=1;
    for(int i=0;i<c;i++) for(int j=0;j<c;j++) g[i][j]=1e9;
    for(int x=0;x<c;x++){
        for(int y=0;y<c;y++) if(x!=y)
            for(int i:ce[x])
                for(int j:ce[y])
                    ckmin(g[x][y],a[i][to[i]]-a[i][j]);
        for(int i:ce[x]){
            for(int j=0;j<Σ;j++) if(!onc[j])
                ckmin(g[x][x],a[i][to[i]]-a[i][j]);
            ckmin(g[x][x],a[i][to[i]]-a[i][i]-k);
        }
    }
    // for(int x=0;x<c;x++)
    //     for(int y=0;y<c;y++)
    //         printf("g[%d,%d] = %d\n",x,y,g[x][y]);
    for(int s=1;s<(1<<c);s++){
        for(int i=0;i<c;i++) if(s>>i&1) dp[s]+=g[i][i];
        for(int i=0;i<c;i++)if(s>>i&1){
            for(int j=0;j<c;j++)if((s>>j&1)&&i!=j){
                ckmin(dp[s],dp[s^1<<i]+g[i][j]);
            }
        }
    }
    ans+=dp[(1<<c)-1];
    printf("%d",ans);
}
/*
input:
15 1
ecebaecaedbbacd
cddadbdbaaeabbe

output:
13

answer:
12

explanation:
*/