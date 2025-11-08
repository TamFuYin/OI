#include<bits/stdc++.h>
const int N=1e5,M=1e5;
int nx[M],ls[N],to[M],tot;
void add(int u,int v){
	nx[++tot]=ls[u];
	to[ls[u]=tot]=v;
}
int mark[N];
bool dfs(int u,int cur=1){
	mark[u]=cur;
	for(int i=ls[u];i;i=nx[i]){
		if(!mark[to[i]]){
			if(!dfs(to[i],cur^3))
				return 0;
		}
		else if(mark[to[i]]==cur){
			return 0;
		}
	}
	return 1;
}
std::vector<int> v[3];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		std::fill(ls+1,ls+n+1,0),tot=0;
		while(m--){
			int u,v;scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		std::fill(mark+1,mark+n+1,0);
		bool b=0;
		for(int i=1;i<=n;i++){
			if(!mark[i]) if(!dfs(i)) {b=1;break;}
			v[mark[i]].push_back(i);
		}
		if(b){
			puts("Alice"),fflush(stdout);int _;
			while(n--) puts("1 2"),fflush(stdout),scanf("%d%d",&_,&_);
			continue;
		}
		puts("Bob"),fflush(stdout);
		while(n--){
			int a,b;scanf("%d%d",&a,&b);
			if(a>b) std::swap(a,b);
			if(a==1&&!v[1].empty()){
				printf("%d 1\n",v[1].back()),v[1].pop_back(),fflush(stdout);
				continue;
			}
			if((a==2||b==2)&&!v[2].empty()){
				printf("%d 2\n",v[2].back()),v[2].pop_back(),fflush(stdout);
				continue;
			}
			if(!v[1].empty()){
				printf("%d 3\n",v[1].back()),v[1].pop_back(),fflush(stdout);
				continue;
			}
			if(!v[2].empty()){
				printf("%d 3\n",v[2].back()),v[2].pop_back(),fflush(stdout);
				continue;
			}
		}
	}
}
