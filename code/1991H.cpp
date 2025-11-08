#include<bits/stdc++.h>
const int N=2e5+10;
bool np[N];
std::bitset<N> f,f0,f1,g,fp;
std::vector<int> vf0,p;
//int ff[N],gg[N];
int main(){
	for(int i=2;i<N;i++){
		if(!np[i]) p.push_back(i);
		for(int j:p){
			if(j*i>=N) break;
			np[j*i]=1;
			if(i%j==0) break;
		}
	}
	for(int i:p) f[i+2]=!f[i];
	for(int i:p) if(!f[i]) f0[i]=1,vf0.push_back(i);
	for(int i:vf0) f|=f0<<i;
	for(int i:p) if(f[i]) fp[i]=1;
	for(int i=1;i<N;i++) if(fp[i]) g|=fp<<i;
	g&=f;
	int T;scanf("%d",&T);
	while(T--){
		int n,cf=0,cg=0;scanf("%d",&n);
		for(int i=1,a;i<=n;i++)
			scanf("%d",&a),cf+=f[a],cg+=g[a];
		if(cf==n&&(n&1)){
			if(!cg) puts("bob");
			else if(cg==n) puts("bob");
			else puts("alice");
			continue;
		}
		if(!cf) puts("bob");
		else puts("alice");
	}
}
