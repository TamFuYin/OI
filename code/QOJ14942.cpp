#include<bits/stdc++.h>
int n,m;
const int N=1e6+10;
std::vector<int> p[N];
int a[N];
std::mt19937 rnd(114514);
void construct(){
    std::iota(a,a+m,1);
    for(int i=1;i<=m*2;i++){
        std::shuffle(a,a+m,rnd);
        std::copy(a,a+m,p[i].begin());
    }
}
void recode(){
    while(n--){
        scanf("%d",&x);
        for(int i=1;i<=m;i++) printf("%d ",i);
        for(int i=0;i<m;i++) printf("%d ",p[x][i]);
        for(int i=0;i<m;i++) printf("%d ",p[m+x][i]);
    }
}
void decode(){
    while(n--){
    }
}
int main(){
    int op;scanf("%d%d%d",&op,&n,&m);
    construct();
    if(op==1) recode();
    else decode();
}