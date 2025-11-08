#include<cstdio>
const int N=1e5+10;
int a[N],b[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;bool bj=0;
		scanf("%d",&n);
		for(int i=1;i<n;i++) scanf("%d",&b[i]);
		a[1]=b[1];b[n]=0;
		for(int i=2;i<=n;i++){
			a[i]=b[i]|b[i-1];
			if((a[i-1]&a[i])!=b[i-1]){
				puts("-1");
				bj=1;
				break;
			}
		}
		if(bj) continue;
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		puts("");
	}
}
