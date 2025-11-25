#include<bits/stdc++.h>
const int N=2e5+10;
int a[N];
bool b[N],b1[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,k,q;scanf("%d%d%d",&n,&k,&q);
        std::fill(b+1,b+n+1,0);
        std::fill(b1+1,b1+n+1,0);
        while(q--){
            int c,l,r;scanf("%d%d%d",&c,&l,&r);
            if(c==2) std::fill(b+l,b+r+1,1);
            else std::fill(b1+l,b1+r+1,1);
        }
        for(int i=1,las=-1;i<=n;i++){
            if(b[i]&&b1[i]) printf("%d ",k+1),las=-1;
            else if(!b[i]) printf("%d ",k),las=-1;
            else ++las,las%=k,printf("%d ",las);
        }
        puts("");
    }
}