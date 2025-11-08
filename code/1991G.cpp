#include<cstdio>
const int N=1e5;
char s[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m,k,q;scanf("%d%d%d%d%s",&n,&m,&k,&q,s);
		int h1=k,h2=0,v1=k,v2=0;
		for(int i=0;i<q;i++){
			if(n==k&&m==k){
				puts("1 1");
				continue;
			}
			if(n==k){
				if(s[i]=='H'){
					++h2;
					printf("%d %d\n",h2,1);
					if(h2==k) h2=0;
				}
				else{
					printf("%d %d\n",1,k+1);
				}
				continue;
			}
			if(m==k){
				if(s[i]=='V'){
					++v2;
					printf("%d %d\n",1,v2);
					if(v2==k) v2=0;
				}
				else{
					printf("%d %d\n",k+1,1);
				}
				continue;
			}
//			printf("%d %c: ",i+1,s[i]);
			if(s[i]=='H'){
				if(h1<n) {++h1;printf("%d %d\n",h1,1);}
				else{
					++h2;
					printf("%d %d\n",h2,1);
					if(h2==k){
						if(v1==m){
							v1=k;
							h2=0;
						}
						else{
							h1=k;
							h2=0;
						}
					}
				}
			}
			else{
				if(v1<m) {++v1;printf("%d %d\n",1,v1);}
				else{
					++v2;
					printf("%d %d\n",1,v2);
					if(v2==k){
						if(h1==n){
							h1=k;
							v2=0;
						}
						else{
							v1=k;
							v2=0;
						}
					}
				}
			}
		}
	}
}
