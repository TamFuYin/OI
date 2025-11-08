#include"graph.h"
#include<bits/stdc++.h>
std::mt19937 rnd(time(0));
std::vector<int> known;
const int n=100;
bool conn[n+1][n+1];
int ord[n+1],cono[n+1];
void get_graph(){
	int x,y,z,v;
	while(1){
		x=rnd()%n+1,y=rnd()%n+1,z=rnd()%n+1;
		if(x==y||y==z||z==x) continue;
		v=query(x,y,z);
		if(v==0||v==3) break;
	}
	conn[x][y]=conn[y][z]=conn[x][z]=v==0?0:1;
	known={x,y,z};
	std::iota(ord+1,ord+n+1,1);
	std::shuffle(ord+1,ord+n+1,rnd);
	for(int i=1;i<=n;i++){
		int u=ord[i];
		if(u!=x&&u!=y&&u!=z){
			bool have0=0,have2=0;
			for(int j=1;j<known.size();j++){
				cono[j]=query(known[0],known[j],u)-conn[known[0]][known[j]];
				have0|=cono[j]==0;have2|=cono[j]==2;
			}
			assert(!(have0&have2));
			if(!(have0|have2)){
				if(query(known[1],known[2],u)-conn[known[1]][known[2]]==0) have2=1;
				else have0=1;
			}
			conn[known[0]][u]=have0?0:1;
			for(int j=1;j<known.size();j++)
				conn[known[j]][u]=cono[j]-conn[known[0]][u];
			known.push_back(u);
		}
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(conn[known[i]][known[j]]) report(known[i],known[j]);
}
