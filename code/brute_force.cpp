#include<bits/stdc++.h>
const int N=1e3;
int n,m,e,q;
const int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
int d[N][N][4];
char s[N];
int c[N][N],l[N][N];
bool vis[N][N],p[N][N];
int ans;
void anyway(int x,int y,bool col,int lv){
	if(vis[x][y]) return;
	vis[x][y]=1;
	if(p[x][y]){
		if(c[x][y]!=col&&l[x][y]<=lv) ++ans;
		return;
	}
	++ans;
	for(int i=0;i<4;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(d[x][y][i]==3){
			anyway(tx,ty,col,lv);
		}
	}
}
void straight(int x,int y,int i,int col,int lv){
	while(d[x][y][i]==2){
		x+=dx[i],y+=dy[i];
//		printf("!2 %d %d\n",x,y);
		if(!vis[x][y]){
			vis[x][y]=1;
			if(p[x][y]){
				if(c[x][y]!=col&&l[x][y]<=lv) ++ans;
				return;
			}
			++ans;
		}
	}
}
int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);e=0;
		memset(d+1,0,sizeof(int)*n*m*4);
		for(int i=1;i<=n;i++){
			scanf("%s",s+1);
			for(int j=1;j<m;j++)
				d[i][j][1]=d[i][j+1][0]=s[j]-'0';
		}
		for(int i=1;i<n;i++){
			scanf("%s",s+1);
			for(int j=1;j<=m;j++)
				d[i][j][3]=d[i+1][j][2]=s[j]-'0';
		}
		for(int i=1;i<=q;i++){
			int col,lv,x,y;scanf("%d%d%d%d",&col,&lv,&x,&y);
			memset(vis,0,sizeof vis);ans=0;
			anyway(x,y,col,lv);
			for(int j=0;j<4;j++){
//				printf("%d: %d\n",j,d[x][y][j]);
				straight(x,y,j,col,lv);
				if(d[x][y][j]==1){
					int tx=x+dx[j],ty=y+dy[j];
					if(!vis[tx][ty]&&(!p[tx][ty]||c[tx][ty]!=col&&l[tx][ty]<=lv)){
//						printf("1 %d %d\n",tx,ty);
						++ans;
					}
				}
			}
			c[x][y]=col,l[x][y]=lv,p[x][y]=1;
			printf("%d\n",ans-1);
		}
	}
}
