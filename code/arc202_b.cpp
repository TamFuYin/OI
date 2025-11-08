#include<bits/stdc++.h>
int ans,h,w;
const int N=1e3;
bool vis[N][N];
void dfs(int x,int y,int t){
	if(x==0&&y==0&&t==h*w){
		++ans;
		return;
	}
	int tx=(x-2+h)%h,ty=(y-1+w)%w;
	if(!vis[tx][ty]) vis[tx][ty]=1,dfs(tx,ty,t+1),vis[tx][ty]=0;
	if((y+1)%w!=ty){
		ty=(y+1)%w;
		if(!vis[tx][ty]) vis[tx][ty]=1,dfs(tx,ty,t+1),vis[tx][ty]=0;
	}
}
int main(){
	for(h=1;h<=10;h++){
		for(w=1;w<=10;w++){
			ans=0;
			dfs(0,0,0);
			printf("%d ",ans);
		}
		puts("");
	}
}
