#include<bits/stdc++.h>
int main(){
	for(int n=300;n<=306;n++){
		char s[7];sprintf(s,"%d.txt",n);
		freopen(s,"w",stdout);
		for(int i=1;i<=n;i++){
			if(i&1) for(int j=1;j<=n;j++) printf("%d",j&1);
			else for(int j=1;j<=n;j++) printf("0");
			puts("");
		}
	}
}
