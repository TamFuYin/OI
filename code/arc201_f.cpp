#include<bits/stdc++.h>
namespace TFX{
	void main(){
		using ll=long long;
		ll x=0,y=0,z=0,xy=0,yz=0,xz=0,xyz=0;
		int n;scanf("%d",&n);
		using std::min;
		for(int i=1;i<=n;i++){
			int a,b,c,d,e;
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
			x+=min({a,b,c});
			y+=min({b,c,d});
			z+=min({c,d,e});
			xy+=min({a+d,b,c});
			yz+=min({b+e,c,d});
			xz+=min({min(a,b)+min(d,e),c});
			xyz+=min({a+d,b+e,b+d,c});
			printf("%lld ",min({x,y,z,xy/2,yz/2,xz/2,xyz/3}));
		}
		puts("");
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--) TFX::main();
}