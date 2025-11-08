#include<bits/stdc++.h>
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		int nx=0,ny=0,nz=0;
		for(int i=1,x,y,z;i<=n;i++){
			scanf("%d%d%d",&x,&y,&z);
			if(x>=y&&x>=z) ++nx;
			else if(y>=x&&y>=z) ++ny;
			else ++nz;
		}
	}
}