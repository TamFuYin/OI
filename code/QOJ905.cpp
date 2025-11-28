// 模板·「三元环枚举」
#include<bits/stdc++.h>
const int MOD=998244353;
const int N=1e5+7;
int x[N];
std::vector<int> g[N],dag[N];
bool vis[N];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",x+i);
    for(int i=0,u,v;i<m;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    for(int i=0;i<n;i++)
        for(int j:g[i])
            if(g[i].size()>g[j].size()||g[i].size()==g[j].size()&&i>j)
                dag[i].push_back(j);
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j:dag[i]) vis[j]=1;
        for(int j:dag[i]){
            for(int k:dag[j]) if(vis[k]) (ans+=1ll*x[i]*x[j]%MOD*x[k]%MOD)%=MOD;
        }
        for(int j:dag[i]) vis[j]=0;
    }
    printf("%d\n",ans);
}