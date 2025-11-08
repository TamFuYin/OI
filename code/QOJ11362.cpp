#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
const int N=2e5+10;
std::unordered_set<int> Q[3];
struct pairHash{
    size_t operator()(const std::pair<int,int>& p)const{
        return std::hash<int>{}(p.first)^std::hash<int>{}(p.second);
    }
};
struct pairEqual{
    bool operator()(const std::pair<int,int>& p,const std::pair<int,int>& q)const{
        return p.first==q.first&&p.second==q.second||p.second==q.first&&p.first==q.second;
    }
};
using ll=long long;
std::unordered_map<std::pair<int,int>,ll,pairHash,pairEqual> edge;
template<typename T>void ckmax(T& a,T b){a=std::max(a,b);}
std::unordered_set<int> to[N];
ll ans;
void insert_edge(int u,int v,ll w){
    if(edge.find({u,v})!=edge.end())
        ckmax(ans,edge[{u,v}]+w),
        ckmax(edge[{u,v}],w);
    else if(u==v) ckmax(ans,w);
    else{
        edge[{u,v}]=w;
        if(to[u].size()==1||to[u].size()==2) Q[to[u].size()].erase(u);
        if(to[v].size()==1||to[v].size()==2) Q[to[v].size()].erase(v);
        to[u].insert(v);
        to[v].insert(u);
        if(to[u].size()==1||to[u].size()==2) Q[to[u].size()].insert(u);
        if(to[v].size()==1||to[v].size()==2) Q[to[v].size()].insert(v);
    }
}
void erase_edge(int u,int v){
    edge.erase({u,v});
    if(to[u].size()==1||to[u].size()==2) Q[to[u].size()].erase(u);
    if(to[v].size()==1||to[v].size()==2) Q[to[v].size()].erase(v);
    to[u].erase(v);
    to[v].erase(u);
    if(to[u].size()==1||to[u].size()==2) Q[to[u].size()].insert(u);
    if(to[v].size()==1||to[v].size()==2) Q[to[v].size()].insert(v);
}
int main(){
    // freopen(".in","r",stdin);
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        insert_edge(u,v,w);
    }
    while(!Q[1].empty()||!Q[2].empty()){
        if(!Q[1].empty()){
            int u=*Q[1].begin();
            erase_edge(u,*to[u].begin());
        }
        else{
            int u=*Q[2].begin(),v=*to[u].begin(),w=*++to[u].begin();
            ll vw=edge[{u,v}],ww=edge[{u,w}];
            erase_edge(u,v),erase_edge(u,w);
            insert_edge(v,w,vw+ww);
        }
    }
    printf("%lld",ans);
}