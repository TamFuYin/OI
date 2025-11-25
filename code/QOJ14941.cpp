#include<bits/stdc++.h>
const int N=1e5;
int A[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m,a,b;scanf("%d%d%d%d",&n,&m,&a,&b);
        std::fill(A,A+n*m+1,0);
        for(int i=1,c;i<=n*m;i++) scanf("%d",&c),++A[c];
        std::sort(A+1,A+n*m+1,[](int x,int y){return x<y;});
        int ans=0;
        for(int i=1,B=A[0];i<=n*m;i++)
            ans+=std::min(a*A[i],b*B),B+=A[i];
        printf("%d\n",ans);
    }
}