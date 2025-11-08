#include<bits/stdc++.h>
int main(){
    int n;scanf("%d",&n);
    if(n==1){
        puts("0");
        return 0;
    }
    if(n<6){
        puts("-1");
        return 0;
    }
    printf("%d\n",(n/2)*(n-n/2-1));
    for(int i=1;i<=n/2;i++){
        for(int j=n/2+1;j<=n;j++){
            if(i+j!=n+(n%2==0)){
                printf("%d %d\n",i,j);
            }
        }
    }
}