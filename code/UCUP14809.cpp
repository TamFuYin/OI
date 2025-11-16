#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){a=std::min(a,b);}
const int N=2e3+10,M=5e3+10;
double f[N][M][2][2];
int main(){
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int n,m;std::cin>>n>>m;
    f[0][m][0][0]=0;
    for(int i=1;i<=n;i++){
        int a,b,c,d,e,p;
        std::cin>>a>>b>>c>>d>>e>>p;
        for(int x=0;x<=1;x++){
            for(int y=0;y<=1;y++){
                for(int j=b;j<=m;j++)
                    ckmin(f[i][j-b][x|1][y],(f[i-1][j][x][y]+a)*p),
                    ckmin(f[i][j-b][x][y|1],(f[i-1][j][x][y]+a)*(1-p));
            }
        }
    }
}