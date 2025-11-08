#include<bits/stdc++.h>
const int N=2e3+10;
void insert(int b[],int x){
	for(int i=29;i>=0;i--){
		if(x>>i&1){
			if(b[i]) x^=b[i];
			else {b[i]=x;return;}
		}
	}
}
int next(int b[],int x,int y){
	if(y==INT_MAX) return INT_MAX;
	for(int i=29;i>=0;i--){
		if((y>>i&1)&&!(x>>i&1)){
			if(!b[i]){
				for(int j=i+1;j<30;j++) if(!(x>>j&1)&&b[j]){
					x^=b[j];
					for(int k=j-1;k>=0;k--)
						if((x>>k&1)&&b[k]) x^=b[k];
					return x;
				}
				return INT_MAX;
			}
			else x^=b[i];
		}
		if(!(y>>i&1)&&(x>>i&1)){
			if(!b[i]){
				for(int j=i-1;j>=0;j--) if((x>>j&1)&&b[j]) x^=b[j];
				return x;
			}
			else x^=b[i];
		}
	}
	for(int i=0;i<30;i++) if(!(x>>i&1)&&b[i]){
		x^=b[i];
		for(int j=i-1;j>=0;j--)
			if((x>>j&1)&&b[j]) x^=b[j];
		return x;
	}
	return INT_MAX;
}
int b[N][30],a[N];
int f[N][N],g[N][N];
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		memcpy(b[i+1],b[i],sizeof(int)*30);
		insert(b[i+1],a[i]);
	}
	for(int i=1;i<=n;i++) g[0][i]=INT_MAX;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=next(b[i],a[i],g[i-1][j-1]);
			g[i][j]=std::min(g[i-1][j],f[i][j]);
//			printf("[%d,%d] %d %d\n",i,j,f[i][j],g[i][j]);
		}
	}
	for(int i=n;i>=1;i--) if(g[n][i]!=INT_MAX) {printf("%d",i);return 0;}
}
