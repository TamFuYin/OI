#include<cstdio>
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		switch(n){
			case 1:printf("1\n1\n");break;
			case 2:printf("2\n1 2\n");break;
			case 3:printf("2\n1 2 2\n");break;
			case 4:printf("3\n1 2 2 3\n");break;
			case 5:printf("3\n1 2 2 3 3\n");break;
			default:
				puts("4");
				for(int i=1;i<=n;i++) printf("%d ",(i-1)%4+1);
				puts("");
		}
	}
}
