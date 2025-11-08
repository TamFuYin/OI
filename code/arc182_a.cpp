#include<cstdio>
const int Q=5e3+10;
int v[Q],p[Q],f[Q];
int main(){
	int n,q;scanf("%d%d",&n,&q);
	int ans=1;
	for(int i=1;i<=q;i++) scanf("%d%d",&p[i],&v[i]);
	for(int i=1;i<=q;i++){
		for(int j=i+1;j<=q;j++){
			if(v[i]>v[j]){
				if(p[i]<p[j]){
					if(f[i]==1) ans=0;
					else f[i]=-1;
					if(f[j]==-1) ans=0;
					else f[j]=1;
				}
				else if(p[i]>p[j]){
					if(f[i]==-1) ans=0;
					else f[i]=1;
					if(f[j]==1) ans=0;
					else f[j]=-1;
				}
				else ans=0;
			}
		}
	}
	const int MOD=998244353;
	for(int i=1;i<=q;i++) if(f[i]==0) ans=ans*2%MOD;
	printf("%d",ans);
}
