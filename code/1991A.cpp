#include<bits/stdc++.h>
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int ans=0,n;scanf("%d",&n);
		for(int i=1,a;i<=n;i++){
			scanf("%d",&a);
			if(i&1) ans=std::max(ans,a);
		}
		printf("%d\n",ans);
	}
}
