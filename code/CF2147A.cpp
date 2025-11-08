#include<bits/stdc++.h>
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int x,y;scanf("%d%d",&x,&y);
        if(x<y) puts("2");
        else if(1<y&&y<x-1) puts("3");
        else puts("-1");
    }
}