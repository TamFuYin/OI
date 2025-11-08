/*
最小团覆盖，调整法
1. 依次考虑每个团，依次考虑每个不在团中的点，查看这个点是否与团中所有点相连，如果是，则加入这个点
2. 依次考虑每个团，如果删去这个团后仍然是合法的，则删去它
3. 依次考虑每个团，依次考虑每个团中的点，如果删去它后仍然合法，则删去它
*/
#include<bits/stdc++.h>
const int N=1e5+5,M=2e5+5;
std::vector<int> to[N];
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
std::unordered_map<std::pair<int,int>,int,pair_hash> cnt;
std::vector<int> cli[N];
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int pc[N],npc[N],pn[N];
int main(){
    freopen("QOJ4905/friends0.in","r",stdin);
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        to[u].emplace_back(v);
        to[v].emplace_back(u);
        cnt[{u,v}]=1;
        cli[i]={u,v};
    }
    for(int i=1;i<=n;i++) std::sort(to[i].begin(),to[i].end());
    pc[0]=m;std::iota(pc+1,pc+pc[0]+1,1);
    bool ok;
    do{
        ok=false;
        std::shuffle(pc+1,pc+pc[0]+1,rnd);
        for(int i=1;i<=pc[0];i++){
            auto& c=cli[pc[i]];
            std::iota(pn+1,pn+n+1,1);
            std::shuffle(pn+1,pn+n+1,rnd);
            for(int j=1;j<=n;j++){
                int x=pn[j];
                if(std::find(c.begin(),c.end(),x)!=c.end()) continue;
                ok=true;
                for(int y:c) if(!std::binary_search(to[x].begin(),to[x].end(),y)){ok=false;break;}
                if(ok){
                    for(int y:c) cnt[{x,y}]++;
                    c.push_back(x);
                    break;
                }
            }
            if(ok) break;
        }
        for(int i=1;i<=pc[0];i++){
            auto& c=cli[pc[i]];
            ok=true;
            for(int j=0;j<(int)c.size();j++)
                for(int k=j+1;k<(int)c.size();k++)
                    if(cnt[{c[j],c[k]}]==1) {ok=false;break;}
            if(ok){
                for(int j=0;j<(int)c.size();j++)
                    for(int k=j+1;k<(int)c.size();k++)
                        --cnt[{c[j],c[k]}];
                c.clear();
                break;
            }
        }
        npc[0]=0;
        for(int i=1;i<=pc[0];i++){
            auto c=cli[pc[i]];
            if(!c.empty()) npc[++npc[0]]=pc[i];
        }
        std::swap(pc,npc);
        if(ok) continue;
        for(int i=1;i<=pc[0];i++){
            auto& c=cli[pc[i]];
            std::shuffle(c.begin(),c.end(),rnd);
            for(std::vector<int>::iterator j=c.begin(),nx;j!=c.end();j=nx){
                int x=*j;nx=std::next(j);
                ok=true;
                for(int y:c) if(x!=y&&cnt[{x,y}]==1) {ok=false;break;}
                if(ok){
                    c.erase(j);
                    for(int y:c)
                        --cnt[{x,y}];
                    break;
                }
            }
            if(ok) break;
        }
        for(int i=1;i<=pc[0];i++){
            auto& c=cli[pc[i]];
            std::sort(c.begin(),c.end());
            for(int x:c) fprintf(stderr,"%d ",x);
            fprintf(stderr,"\n");
        }
        fprintf(stderr,"\n");
    }while(ok);
    printf("%d\n",pc[0]);
    for(int i=1;i<=pc[0];i++){
        auto& c=cli[pc[i]];
        std::sort(c.begin(),c.end());
        printf("%d",c.size());
        for(int x:c) printf(" %d",x);
        puts("");
    }
}