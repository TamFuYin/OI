#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
const int tx[]={1,1,-1,-1},ty[]={1,-1,-1,1};
const int N=1e4;
char a[N*2][N*2];
int lowbit(int x){
	return x&-x;
}
int main(){
	for(int i=0;i<N*2;i++)
		for(int j=0;j<N*2;j++)
			a[i][j]=' ';
	int x=0,y=0,c=0;
	int mnx=0,mny=0,mxx=0,mxy=0;
	for(int i=1;i<=1<<17;i++){
		a[N+std::min(x,x+tx[c])][N+std::min(y,y+ty[c])]=c%2?'\\':'/';
		x+=tx[c],y+=ty[c];
//		printf("%d,%d\n",x,y);
		int d=i/lowbit(i)/2%2?1:-1;
		c=(c+d+4)%4;
		ckmin(mnx,x);
		ckmax(mxx,x);
		ckmin(mny,y);
		ckmax(mxy,y);
	}
	for(int y=mxy;y>=mny;y--){
		for(int x=mnx;x<=mxx;x++)
			putchar(a[N+x][N+y]);
		puts("");
	}
}
