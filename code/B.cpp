#include<cstdio>
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,k;
        scanf("%d%d",&n,&k);
        if(k<=4*n-4) printf("%d\n",(k+1)/2);
        else printf("%d\n",k-(2*n-2));
    }
}