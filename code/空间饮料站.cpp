#include<bits/stdc++.h>
const int N=ceil(log2(5e3)),MOD=998244353;
using poly=std::array<N>;
int w[N];
void NTT(poly a,bool t=1){
	
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	while(m--){
		int op;scanf("%d",&op);
		if(op<=2){
			int i,c;scanf("%d%d",&i,&c);
			if(op==2) c=-c;
			update(i,c);
		}
		else{
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			printf("%d",query(l,r)[k]);
		}
	}
}