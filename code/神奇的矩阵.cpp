#include<bits/stdc++.h>
const int N=1e3+10;
int n;
struct matrix{
	int a[N][N];
	void read(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",a[i]+j);
	}
}a,b,c;
std::mt19937 rnd(time(0));
const int MOD=1e9+9;
struct vector{
	int a[N];
	void rand(){
		for(int i=1;i<=n;i++) a[i]=rnd()%MOD;
	}
	void clear(){
		std::fill(a+1,a+n+1,0);
	}
	bool operator!=(const vector& b){
		for(int i=1;i<=n;i++)
			if(a[i]!=b.a[i]) return 1;
		return 0;
	}
}v;
vector operator*(const matrix& a,const vector& b){
	vector c;c.clear();
	for(int i=1;i<=n;i++){
		for(int k=1;k<=n;k++){
			(c.a[i]+=1ll*a.a[i][k]*b.a[k]%MOD)%=MOD;
		}
	}
	return c;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		a.read();b.read();c.read();
		bool flag=0;
		for(int i=1;i<=10;i++){
			v.rand();
			if((a*(b*v))!=(c*v)) puts("No"),flag=1;
			if(flag) break;
		}
		if(flag) continue;
		puts("Yes");
	}
}