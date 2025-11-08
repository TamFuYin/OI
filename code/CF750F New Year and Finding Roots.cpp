#include<bits/stdc++.h>
int ask(int u){
	printf("! %d\n",u);
	fflush(stdout);
	scanf("%d",&u);
	return u;
}
std::mt19937 rnd(time(0));
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int h;scanf("%d",&h);
		int n=(1<<h)-1;
		int u=rnd()%n+1;
		switch(ask(u)){
			case 1:break;
			case 2:
			printf("%d\n",u);
			goto Continue;
			break;
			case 3:break;
		}
		Continue:;
	}
}