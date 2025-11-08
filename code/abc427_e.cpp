#include<bits/stdc++.h>
const int N=13;
char s[N][N];
struct point{}
std::vector<std::pair<int,int>> trash;
int main(){
    int h,w;scanf("%d%d",&h,&w);
    for(int i=1;i<=h;i++){
        scanf("%s",s[i]+1);
        for(int j=1;j<=w;j++){
            if(s[i][j]=='#') s[i][j]=1;
            else s[i][j]=0;
        }
    }
}