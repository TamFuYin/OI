// #include"permgame.h"
#include<bits/stdc++.h>
using vi=std::vector<int>;
int Bob(vi);
std::vector<vi> a;
const int N=1e5;
bool vis[N];
vi p;
vi operator+(const vi& a,const vi& b){
	vi tmp=a;
	tmp.insert(tmp.end(),b.begin(),b.end());
	return tmp;
}
vi run(int x){
	return vi{x}+(vis[p[x]]?vi{}:run(p[x]));
}
int Alice(int m,int e,vi u,vi v,int n,vi _p){
	p=_p;
	a.clear();
	std::fill(vis,vis+n,0);
	for(int i=0;i<n;i++) if(!vis[i]) a.push_back(run(i));
	if(m==2){
		for(int i=0;i<n;i++){
			while(p[i]!=i){
				Bob({i,p[i]});
				std::swap(p[i],p[p[i]]);
			}
		}
		return n;
	}
	if(e>m){
		int k=0;
		for(auto c:a) k+=c.size()==1;
		return k;
	}
	if(e==m-1){
		int last=-1;
		for(auto c:a){
			if(1<c.size()){
				if(~last){
				}
			}
		}
	}
}