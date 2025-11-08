#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=1e5;
bool del[N],newdel[N];
std::pair<int,int> f[N];
std::vector<int> lim[N];
std::vector<int> b;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        int m=n*n+1;
        std::fill(del+1,del+m+1,0);
        std::fill(f+1,f+m+1,std::make_pair(1,0));
        for(int i=1;i<=m;i++) lim[i].clear();
        for(int t=1;t<=n;t++){
            b.clear();
            for(int i=1;i<=m;i++) if(!del[i]) b.push_back(i);
            printf("? %d ",(int)b.size());
            for(int i:b) printf("%d ",i);
            puts(""),fflush(stdout);
            int cnt;scanf("%d",&cnt);
            if(cnt>=n+1){
                b.clear();
                while(cnt--){int i;scanf("%d",&i);b.push_back(i);}
                printf("! ");
                for(int i=0;i<=n;i++) printf("%d ",b[i]);
                puts(""),fflush(stdout);
                goto Continue;
            }
            std::fill(newdel+1,newdel+m+1,0);
            while(cnt--){
                int j;scanf("%d",&j);del[j]=1;newdel[j]=1;
            }
            for(int i=1,las=0;i<=m;i++){
                if(!del[i]){
                    if(las){
                        if(lim[i].empty()||lim[i].back()!=las)
                        lim[i].push_back(las);
                    }
                }
                else if(newdel[i]) las=i;
            }
        }{
        int s=0;
        for(int i=1;i<=m;i++)
            for(int j:lim[i]) ckmax(f[i],std::make_pair(f[j].first+1,j));
        for(int i=1;i<=m;i++) if(f[i].first>=n+1) s=i;
        assert(s!=0);
        static std::stack<int> b;
        while(!b.empty()) b.pop();
        while(s) b.push(s),s=f[s].second;
        printf("! ");
        ++n;
        while(n--) printf("%d ",b.top()),b.pop();
        puts("");fflush(stdout);
        }Continue:;
    }
}