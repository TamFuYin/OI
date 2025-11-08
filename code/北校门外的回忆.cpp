#include<bits/stdc++.h>
int main(){
	int n,q,K;scanf("%d%d%d",&n,&q,&K);
	while(q--){
		int op,x,v;scanf("%d%d",&op,&x);
		if(op==1) scanf("%d",&v),add(x,v);
		else printf("%d\n",query(x));
	}
}