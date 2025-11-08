#include<bits/stdc++.h>
const int N=21;
bool exis[N][N],cons[N][N];
int f[N][1<<N];
int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);--n;
	for(int i=1,a,b,c;i<=k;i++){
		scanf("%d%d%d",&a,&b,&c);
		--b;
		exis[a][b]=1;
		cons[a][b]=c;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int S=0;S<(1<<n);S++)
		if(f[i-1][S]){
			for(int T=0;T<(1<<n);T++){
				bool no=0;
				for(int j=0,t=0,s=0;j<n;j++){
					t+=T>>j&1;s+=S>>j&1;
					if(t<s||exis[i][j]&&cons[i][j]!=(T>>j&1)){
						no=1;
						break;
					}
				}
				if(no) continue;
				f[i][T]+=f[i-1][S];
				// printf("%d %d->%d\n",i,S,T);
			}
		}
	}
	int ans=0;
	for(int i=0;i<(1<<n);i++) ans+=f[m][i];
	printf("%d",ans);
}