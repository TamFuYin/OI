#include<bits/stdc++.h>
std::multimap<int,int> s;
const int N=1e5+10;
int cnt[N];
int bel[N];
std::vector<int> tr[N];
int main(){
    // freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n,ans=0;scanf("%d",&n);
        std::fill(cnt+1,cnt+n+1,0);s.clear();
        for(int i=1;i<=n;i++){
            int a;scanf("%d",&a);
            if(s.upper_bound(a)==s.begin()) ++ans,tr[bel[i]=i]={i};
            else{
                auto it=--s.upper_bound(a);
                int j=it->second;
                if(++cnt[j]==2) s.erase(it);
                tr[bel[i]=bel[j]].push_back(i);
            }
            s.emplace(a,i);
        }
        printf("%d\n",ans);
        for(int i=1;i<=n;i++) if(bel[i]==i){
            printf("%d ",(int)tr[i].size());
            for(int j:tr[i]) printf("%d ",j);
            puts("");
        }
    }
}