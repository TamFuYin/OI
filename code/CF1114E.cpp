#include<bits/stdc++.h>
int tmp;
int b[100];
std::mt19937 rnd(time(0));
int main(){
	int n;scanf("%d",&n);
	int l=0,r=1e9,m=60;
	while(l<r){
		int mid=l+r>>1;--m;
		printf("> %d\n",mid),fflush(stdout);
		scanf("%d",&tmp);
		if(tmp==0) r=mid;
		else l=mid+1;
	}
	for(int i=1;i<=m;i++){
		printf("? %d\n",rnd()%n+1),fflush(stdout);
		scanf("%d",b+i);
	}
	b[0]=l;
	std::sort(b,b+m+1);
	int d=0;
	for(int i=1;i<=m;i++) d=std::__gcd(d,b[i]-b[i-1]);
	printf("! %d %d\n",l-(n-1)*d,d),fflush(stdout);
}