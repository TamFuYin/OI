#include<bits/stdc++.h>
const int N=1e5+10;
int c[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        std::fill(c,c+n+1,0);
        for(int i=1,a;i<=n;i++) scanf("%d",&a),++c[a];
        int ans=0;
        for(int i=0;i<=n;i++) if(c[i]) ans+=c[i]>=i?c[i]-i:c[i];
        printf("%d\n",ans);
    }
}