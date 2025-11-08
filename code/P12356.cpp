#include<bits/stdc++.h>
int main(){
    scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        if((n&1^1)&m&1) {puts("-1");continue;}
        if(n&m&1){
            continue;
        }
        printf("%d\n",(int)ceil(n*1./m));
        for(int i=1;i<=n/2;i+=m/2){
            for(int j=i;j<i+m/2;j++) printf("%d %d ",j,n-j+1);
            
        }
    }
}