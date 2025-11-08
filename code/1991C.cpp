#include<cstdio>
int ans[40];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		bool odd=0,even=0;
		for(int i=1,a;i<=n;i++){
			scanf("%d",&a);
			if(a&1) odd=1;
			else even=1;
		}
		if(odd^even){
			int a=1e9,top=0;
			bool is_odd=odd;
			while(a!=1){
				ans[++top]=a=(a+1)/2;
				if(a&1) is_odd^=1;
			}
			if(is_odd) ans[++top]=1;
			printf("%d\n",top);
			for(int i=1;i<=top;i++)
				printf("%d ",ans[i]);
			puts("");
		}
		else puts("-1");
	}
}
