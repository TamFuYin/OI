#include<bits/stdc++.h>
using ll=long long;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		ll ans=0;
		for(int i=1,a,b,c,d;i<=n;i++){
			scanf("%d%d%d%d",&a,&b,&c,&d);
			if(b>d) ans+=a+b-d;
			else if(a>c) ans+=a-c;
		}
		printf("%lld\n",ans);
	}
}
