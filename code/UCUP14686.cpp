#include<bits/stdc++.h>
const int N=1e6+10;
using ll=long long;
int t[N],tt[N],a[N];
bool b[N];
int ind[N];
std::queue<int> q;
using pii=std::pair<ll,int>;
ll c[N];
std::priority_queue<pii,std::vector<pii>,std::greater<pii>> pq;
bool stoped[N];
std::vector<int> to[N];
void dfs(int u){
    for(int v:to[u])if(v!=tt[u]){
        if(b[u]==b[v]) c[v]=c[u]+std::abs(a[u]-a[v])*2;
        else if(std::abs(a[u]-a[v])<c[u]) c[v]=std::abs(a[u]-a[v]);
        else c[v]=c[u]+(std::abs(a[u]-a[v])-c[u])*2;
        dfs(v);
    }
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",t+i),++ind[t[i]],to[t[i]].push_back(i);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) b[i]=a[t[i]]<a[i];
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(!--ind[t[u]]) q.push(t[u]);
    }
    for(int i=1;i<=n;i++)if(ind[i]){
        int u=i;
        while(ind[u]) ind[u]=0,pq.emplace(c[u]=b[u]==b[t[u]]?LLONG_MAX:std::abs(a[u]-a[t[u]]),u),tt[t[u]]=u,u=t[u];
        while(!pq.empty()){
            int u=pq.top().second;
            if(pq.top().first!=c[u]) {pq.pop();continue;}
            pq.pop();stoped[u]=1;
            if(!stoped[tt[u]]){
                if(b[u]==b[tt[u]]) c[tt[u]]=c[u]+2*std::abs(a[tt[u]]-a[u]);
                else if(std::abs(a[tt[u]]-a[u])<c[u]) c[tt[u]]=std::abs(a[tt[u]]-a[u]);
                else c[tt[u]]=c[u]+2*(std::abs(a[tt[u]]-a[u])-c[u]);
                pq.emplace(c[tt[u]],tt[u]);
            }
        }
        u=i;
        do dfs(u),u=t[u];while(u!=i);
    }
    for(int i=1;i<=n;i++) printf("%lld ",c[i]);
}