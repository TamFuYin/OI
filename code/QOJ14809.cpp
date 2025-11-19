#include<bits/stdc++.h>
template<typename T>
void ckmax(T& a,T b){a=std::max(a,b);}
const double INF=1e18;
const int N=2e3+10,M=5e3+10;
int a[N],b[N],c[N],d[N],e[N],p[N];
double f[N][M][2][2];
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d%d%d",a+i,b+i,c+i,d+i,e+i,p+i);
    for(int i=n;i>=1;i--){
        double pr=p[i]/100.;
        for(int j=0;j<=m;j++){
            for(int x=0;x<=1;x++){
                for(int y=0;y<=1;y++){
                    f[i][j][x][y]=-INF;
                    if(j>=b[i])
                        ckmax(f[i][j][x][y],f[i+1][j-b[i]][1][y]*pr+f[i+1][j-b[i]][x][1]*(1-pr)+a[i]);
                    if(j>=d[i]){
                        if(x&&y){if(j>=d[i]+e[i]) ckmax(f[i][j][x][y],f[i+1][j-d[i]-e[i]][0][0]+c[i]);}
                        else ckmax(f[i][j][x][y],f[i+1][j-d[i]][1][y]*pr+f[i+1][j-d[i]][x][1]*(1-pr)+c[i]);
                    }
                    // if(f[i][j][x][y]!=-INF) printf("f[%d,%d,%d,%d]=%lf\n",i,j,x,y,f[i][j][x][y]);
                }
            }
        }
    }
    if(f[1][m][0][0]<=-INF/2) puts("-1");
    else printf("%.7lf",f[1][m][0][0]);
}