#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=1e3+10;
char mp[N];
int f[N][N],s[N],opt[N][N];
int solve(int a[],int n){
	memset(f,0,sizeof f);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
	for(int l=n;l>=1;l--){
		for(int r=l+1;r<=n;r++){
			for(int i=l;i<r;i++){
				if(f[l][i]+f[i+1][r]+s[r]-s[l-1]>f[l][r]) opt[l][r]=i;
				ckmax(f[l][r],f[l][i]+f[i+1][r]+s[r]-s[l-1]);
			}
			printf("[%d,%d]: %d %d\n",l,r,f[l][r],opt[l][r]);
			if(r-l+1>2)
//				assert(f[l][r-1]+f[l+1][r]<=f[l+1][r-1]+f[l][r]);
				if(!(opt[l][r-1]<=opt[l][r]&&opt[l][r]<=opt[l+1][r]))
					printf("%d %d %d\n",opt[l][r],opt[l][r-1],opt[l+1][r]),
					exit(-1);
		}
	}
	return f[1][n];
}
int a[N],b[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",mp+1);
		for(int j=1;j<=m;j++)
			a[i]+=mp[j]-'0',
			b[j]+=mp[j]-'0';
	}
	printf("%d",solve(a,n)+solve(b,m));
}
