#include<bits/stdc++.h>
const int N=201;
int a[N];
std::bitset<N> buc[N],ans;
std::multimap<int,int> bs;
int bsum[N];
std::map<int,int> set;
int main(){
    const int goal=1e9;
    int n;scanf("%d",&n);
    const int B=36;
    for(int i=0;i<B;i++) bs.emplace(0,i);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        auto it=bs.begin();
        bs.emplace(it->first+a[i],it->second);
        buc[it->second].set(i);
        bs.erase(it);
    }
    for(auto p:bs) bsum[p.second]=p.first;
    for(int s=0;s<(1<<18);s++){
        int sum=0;
        for(int i=0;i<18;i++) if(s>>i&1) sum+=bsum[i];
        set[sum]=s;
    }
    for(int s=0;s<(1<<18);s++){
        int sum=0;
        for(int i=0;i<18;i++) if(s>>i&1) sum+=bsum[18+i];
        auto it=set.find(goal-sum);
        if(it!=set.end()){
            int t=it->second;
            for(int i=0;i<18;i++) if(t>>i&1) ans|=buc[i];
            for(int i=0;i<18;i++) if(s>>i&1) ans|=buc[18+i];
            printf("%d ",ans.count());
            for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
            return 0;
        }
    }
}