#include<bits/stdc++.h>
namespace IO {
	constexpr int MAXSIZE=1<<20;
	char buf[MAXSIZE],*p1,*p2;
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin),p1==p2)?EOF:*p1++)
	int rd(){
		int x=0,f=1;
		char c=gc();
		while(!isdigit(c)){
			if(c=='-') f=-1;
			c=gc();
		}
		while(isdigit(c)) x=x*10+(c^48),c=gc();
		return x*f;
	}
	char pbuf[1<<20],*pp=pbuf;
	void push(const char &c){
		if(pp-pbuf==1<<20) fwrite(pbuf,1,1<<20,stdout),pp=pbuf;
		*pp++=c;
	}
	void write(int x){
//		printf(">>> %d\n",x);
		static int sta[35];
		int top=0;
		do{sta[top++]=x%10,x/=10;}while(x);
		while(top) push(sta[--top]+'0');
	}
}
using namespace IO;
const int N=2e6+10,V=1e9;
std::mt19937 rnd(0x5e4220);
int h[N];
double ans[N];
int x[N],y[N];
int main(){
	int n=rd(),m=rd();
	for(int i=m+1;i<=n;i++) x[i]=rd(),y[i]=rd();
	int c=0;
	while(clock()<1.96*CLOCKS_PER_SEC){
		for(int i=1;i<=m;i++) h[i]=rnd()%V+1;
		for(int i=m+1;i<=n;i++){
			h[i]=std::min(h[x[i]],h[y[i]]);
			ans[i]+=h[i];
		}
		++c;
	}
	for(int i=m+1;i<=n;i++) write((int)round(V/(ans[i]/c)-1)),push('\n');
	fwrite(pbuf,1,pp-pbuf,stdout);
}
