#include<bits/stdc++.h>
const int N=1e6+10;
bool vis[N];
std::vector<int> ans;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,p,q;scanf("%d%d%d",&n,&p,&q);
        int i=0;bool NO=0;
        ans.clear();std::fill(vis,vis+n,0);
        while(1){
            vis[i]=1;ans.push_back(i);
            if(i-q>=0&&!vis[i-q]) i-=q;
            else if(i+p>=n||vis[i+p]) break;
            else i+=p;
        }
        if(ans.size()!=n) puts("-1");
        else{
            for(int i:ans) printf("%d ",i);
            puts("");
        }
    }
}