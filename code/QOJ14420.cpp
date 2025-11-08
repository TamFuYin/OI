#include<bits/stdc++.h>
const int N=1e3;
double f[N][N];
int main(){
    freopen64(".out","w",stdout);
    int a,b;scanf("%d%d",&a,&b);
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            if(!i&&!j) f[i][j]=0;
            else if(!i) f[i][j]=std::max(f[i][j-1]-1,0.);
            else if(!j) f[i][j]=std::max(f[i-1][j]+1,0.);
            else f[i][j]=std::max((i*(f[i-1][j]+1)+j*(f[i][j-1]-1))/(i+j),0.);
            printf("%.4lf ",f[i][j]);
        }
        puts("");
    }
}