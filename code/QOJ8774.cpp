#include<bits/stdc++.h>
const int N=1e3+10;
double f[N][N];
int main(){
    int n,m,p;scanf("%d%d%d",&n,&m,&p);
    f[n][m]=0;
    for(int i=0;i<=m;i++) f[n+1][i]=INFINITY;
    for(int i=0;i<=n;i++) f[i][m+1]=INFINITY;
    for(int i=n;i>=0;i--){
        for(int j=m;j>=0;j--){
            if(i==n&&j==m) continue;
            double a=f[i][j+1],b=f[i+1][j];
            if(a>b) std::swap(a,b);
            if(a+p<=b) f[i][j]=a+p/4.0;
            else f[i][j]=a/2+((b+a)*(b-a)/2+b*(p-b+a))/(2*p);
        }
    }
    printf("%.9lf",f[1][1]);
}