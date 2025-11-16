#include<bits/stdc++.h>
const int X=9,Y=10,N=X*Y;
const int K[]={-2*X-1,-2*X+1,-X-2,+X-2,+2*X-1,+2*X+1,-X+2,+X+2};
const int leg[]={-X,-1,+X,+1};
bool check(int x,int d){
    if(x+d<0||x+d>=N) return 0;
}
// 马先手，车后手，f=0 表示先手赢
bool vis[N][N],f[N][N];
void dfs(int i,int j){}
int main(){
    for(int i=0;i<X*Y;i++)
        for(int j=0;j<X*Y;j++)
            if(!vis[i][j]) dfs(i,j);
}