#include<bits/stdc++.h>
#define gcd(a,b) std::__gcd(a,b)
using bits=std::vector<bool>;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		int g=gcd(gcd(a,b),c);
		int p=gcd(a,b)/g,q=gcd(a,c)/g,r=gcd(b,c)/g;
		if(a!=g*p*q||b!=g*p*r||c!=g*q*r||a==2&&b==2&&c==2){
			puts("NO");continue;
		}
		puts("YES");
		if(p+q+r==3) std::cout<<std::string(a-1,'0')+"01\n"+std::string(a-1,'0')+"10\n"+std::string(a-1,'0')+"11\n";
		else if(p+q==2){
			std::cout<<std::string(a-1,'0')+"1\n";
			std::cout<<std::string(b-1,'0')+"1\n";
			for(int i=0;i<c;i++) printf("%d",(i%a==a-1)^(i%b==b-1));puts("");
		}
		else{
			for(int i=0;i<a;i++) printf("%d",(i/g%p==p-1)^(i/g%q==q-1));puts("");
			for(int i=0;i<b;i++) printf("%d",(i/g%p==p-1)^(i/g%r==r-1));puts("");
			for(int i=0;i<c;i++) printf("%d",(i/g%q==q-1)^(i/g%r==r-1));puts("");
		}
	}
}
