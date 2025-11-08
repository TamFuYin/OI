#include<bits/stdc++.h>
const int N=1e6;
char S[N],X[N],Y[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		using ll=long long;
		scanf("%s%s%s",S,X,Y);
		int xn=strlen(X),yn=strlen(Y),x1=0,y1=0,sn=strlen(S);
		for(int i=0;i<xn;i++) x1+=X[i]=='1';
		for(int i=0;i<yn;i++) y1+=Y[i]=='1';
		int x0=xn-x1,y0=yn-y1;
		if(x1==y1){
			if(xn==yn) puts("Yes");
			else puts("No");
			continue;
		}
		if(1ll*(y0-x0)*sn%(x1-y1)!=0) {puts("No");continue;}
		int tn=1ll*(y0-x0)*sn/(x1-y1),g=std::gcd(sn,tn);
		bool flag=1;
		for(int i=g;i<sn;i++) if(S[i]!=S[i-g]) flag=0;
		puts(flag?"Yes":"No");
	}
}
