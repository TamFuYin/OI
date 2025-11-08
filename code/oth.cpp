#include<bits/stdc++.h>
const int N=8e4+10,B=sqrt(N),lgN=std::__lg(N)+1;
std::vector<int> p;
std::bitset<N> vis;
int n=10;
void sieve(){
	for(int i=2;i<=n;i++){
		if(!vis[i]) p.push_back(i);
		for(int j:p){
			if(i*j>n) break;
			vis[i*j]=1;
			if(i%j==0) break;
		}
	}
}
std::vector<int> qz[N];
int z[N];
std::bitset<N> cur;
void dfsZ(int a,int k){
	if(k==p.size()) return;
	int ori=a;
	dfsZ(a,k+1);a*=p[k];
	if(a>n) return;
	for(int b=p[k];a<=n;a*=p[k],b*=p[k]){
		for(int i=b;i<=n;i+=b) cur[i]=z[std::__gcd(i,a)]&1;
		for(int i=1;i<=n;i++) if((int)cur[i]!=(z[std::__gcd(i,a)]&1)) exit(114514);
		dfsZ(a,k+1);
	}
	for(int i=p[k];i<=n;i+=p[k]) cur[i]=z[std::__gcd(i,ori)]&1;
}
std::mt19937 rnd(time(0));
int main(){
	for(int i=1;i<=n;i++) z[i]=rnd();
	sieve();
	if(z[1]&1) for(int i=1;i<=n;i++) cur[i]=1;
	dfsZ(1,0);
}
