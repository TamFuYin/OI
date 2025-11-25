#include<bits/stdc++.h>
const int N=4e5+10;
int c[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,k;scanf("%d%d",&n,&k);
        std::fill(c+1,c+2*n+1,0);
        for(int i=1,a;i<=n;i++) scanf("%d",&a),++c[a];
        int ans=0;
        for(int i=1,f=0,las=0,beg=0;i<=2*n;i++){
            c[i]+=f;
            if(c[i]>k){
                if(!beg) beg=i;
                ans=std::max(ans,i-beg+c[i]-k);
                f=c[i]-1;
            }
            else{
                beg=0;
                f=0;
            }
        }
        printf("%d\n",ans);
    }
}