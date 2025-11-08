#include<bits/stdc++.h>
const int N=710,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int a[N][N];
int stp[N*N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		std::fill(stp+1,stp+n*m+1,0);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",a[i]+j),stp[a[i][j]]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(x==0||y==0||x==n+1||y==m+1) continue;
					if(a[i][j]==a[x][y]) stp[a[i][j]]=2;
				}
			}
		}
		int sum=0,max=0;
		for(int i=1;i<=n*m;i++)
			sum+=stp[i],max=std::max(max,stp[i]);
		printf("%d\n",sum-max);
	}
}