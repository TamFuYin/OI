const char map[7][8]={
"##   ##",
"## # 2#",
" 1    #",
"  ##   ",
"#    3 ",
"#4 #  #",
"##   ##"
};
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
bool vis[7][7];
int cur=1;
#include<bits/stdc++.h>
std::pair<int,int> sta[100];
int top;
void dfs(int x,int y){
	if(cur==4){
		for(int i=0;i<7;i++)
			for(int j=0;j<7;j++)
				if(map[i][j]==' '&&!vis[i][j])
					return;
		sta[++top]={x,y};
		for(int i=1;i<=top;i++)
			printf("%d %d\n",sta[i].first,sta[i].second);
		puts("");
		--top;
		return;
	}
	sta[++top]={x,y};
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(tx<0||ty<0||tx>=7||ty>=7) continue;
		if(map[tx][ty]=='#'||vis[tx][ty]) continue;
		if(map[tx][ty]!=' '&&map[tx][ty]-'0'!=cur+1) continue;
		if(map[tx][ty]!=' ') ++cur;
		dfs(tx,ty);
		if(map[tx][ty]!=' ') --cur;
	}
	vis[x][y]=0;
	--top;
}
int main(){
	int sx,sy;
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
			if(map[i][j]=='1')
				sx=i,sy=j;
	dfs(sx,sy);
}
