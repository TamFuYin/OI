#include<bits/stdc++.h>
const int N=1e5;
int a[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        std::sort(a+1,a+n+1);
        n=std::unique(a+1,a+n+1)-(a+1);
        printf("%d\n",n*2-1);
    }
}