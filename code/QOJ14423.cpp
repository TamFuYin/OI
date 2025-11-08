#include<bits/stdc++.h>
const int N=1e5;
int p[N],q[N];
std::vector<std::pair<int,int> > opt;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",p+i);
        for(int i=1;i<=n;i++) scanf("%d",q+i);
        bool NO=0;
        opt.clear();
        for(int i=1;i<=n;i++){
            int x=std::find(p+1,p+n+1,i)-p,
            y=std::find(q+1,q+n+1,i)-q;
            if(x>y) {NO=1;break;}
            if(x<y){
                std::swap(p[x],p[y]);
                opt.emplace_back(x,y);
            }
        }
        if(NO) puts("NO");
        else{
            puts("YES");
            printf("%d\n",(int)opt.size());
            for(auto p:opt) printf("%d %d\n",p.first,p.second);
        }
    }
}