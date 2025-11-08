#include<bits/stdc++.h>
const int N=1e3+10;
char mp[N][N];
bool a[N][N];
int r[N],c[N],x[N],y[N];
int n;
bool solve(){
	for(int j=1;j<=n;j++){
		if(a[1][j]){
			y[j]^=1;
			for(int i=1;i<=n;i++) a[i][j]^=1;
		}
	}
	for(int i=2;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=n;j++) cnt+=a[i][j];
		if(cnt*2>=n){
			for(int j=1;j<=n;j++) a[i][j]^=1;
			x[i]^=1;
		}
	}
	for(int j=1;j<=n;j++){
		int cnt=0;
		for(int i=1;i<=n;i++) cnt+=a[i][j];
		if(cnt*2>=n){
			for(int i=1;i<=n;i++) a[i][j]^=1;
			y[j]^=1;
		}
	}
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=n;j++) cnt+=a[i][j];
		if(r[i]!=cnt) return 0;
	}
	for(int j=1;j<=n;j++){
		int cnt=0;
		for(int i=1;i<=n;i++) cnt+=a[i][j];
		if(c[j]!=cnt) return 0;
	}
	return 1;
}
void init(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=mp[i][j]=='1';
	for(int i=1;i<=n;i++) x[i]=y[i]=0;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
		for(int i=1;i<=n;i++) scanf("%d",r+i);
		for(int i=1;i<=n;i++) scanf("%d",c+i);
		init();
		if(solve()) goto YES;
		else{
			init();
			for(int i=1;i<=n;i++) a[1][i]^=1;
			x[1]^=1;
			if(solve()) goto YES;
		}
		puts("No");
		continue;
		YES:
		puts("Yes");
		for(int i=1;i<=n;i++) printf("%d",x[i]);puts("");
		for(int i=1;i<=n;i++) printf("%d",y[i]);puts("");
	}
}
