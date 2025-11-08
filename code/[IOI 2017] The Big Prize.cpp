#include "prize.h"
#include<bits/stdc++.h>
int find_best(int n) {
	std::mt19937 rnd(time(0));
	int x=rnd()%n,T=n;
	while(1){
		auto a=ask(x);
		if(a[0]+a[1]==0) return x;
		if(a[0]>a[1]) x-=rnd()%std::min(T,x+1);
		else x+=rnd()%std::min(T,n-x);
		T*=0.98;
	}
}
