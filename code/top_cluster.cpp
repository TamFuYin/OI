#include<bits/stdc++.h>
const int N=1e5,B=sqrt(N);
int ctfa[N],nclp[N],upep[N],downep[N];
std::vector<int> ep,cl[N];
int curcl[N];
int fa[N];
void addcl(int u,int v){
	if(!v) v=curcl[curcl[0]];
	ctfa[v]=u,nclp[u]=u;
	for(int r=v;r!=u;r=fa[r]) nclp[r]=r;
	for(int i=1;i<=curcl[0];i++){
		int r=curcl[i],j;
		upep[r]=u,downep[r]=v,cl[v].push_back(r);
		for(j=r;!nclp[j];j=fa[j]);
		nclp[r]=nclp[j];
	}
	curcl[0]=0;
}
int sta[N];
int waiting[N],recep[N];
std::vector<int> to[N];
int rectop[N];
void part(int u){
	rectop[u]=sta[0];
	waiting[u]=1;
	int epcnt=0;
	for(int v:to[u]){
		if(v==fa[u]) continue;
		sta[++sta[0]]=v;
		fa[v]=u,part(v);
		waiting[u]+=waiting[v];
		if(recep[v])
			recep[u]=recep[v],
			++epcnt;
	}
	if(waiting[u]>B||epcnt>1||!fa[u]){
		waiting[u]=0,recep[u]=u,ep.push_back(u);
		for(int i=0,j=rectop[u]+1,cnt=0,curdown=0;i<=to[u].size();i++){
			int v=i==to[u].size()?0:to[u][i];
			if(cnt+waiting[v]>B||curdown&&recep[v]||!v){
				for(;(!v||j<rectop[v])&&j<=sta[0];j++)
					curcl[++curcl[0]]=sta[j];
				addcl(u,curdown),cnt=curdown=0;
			}
			cnt+=waiting[v];
			if(recep[v]) curdown=recep[v];
		}
		sta[0]=rectop[u];
	}
}
int main(){}
