#include<bits/stdc++.h>
#define ALL(a) a.begin(),a.end()
const int N=1e5;
using vec=std::basic_string<int>;
using list=std::list<int>;using listit=list::iterator;
vec G[N],T[N];
int dfn[N],dfc,sta[N],top,_n,fa[N],dep[N];
bool in[N],vis[N];
vec bcc,ear;
list c;
listit cit[N];
int dfsta[N];
int back[N];//返祖边
void printbcc(){
	printf("BCC ");
	for(int i:bcc) printf("%d ",i);
	puts("");
}
void printc(){
	printf("C ");
	for(int i:c) printf("%d ",i);
	puts("");
}
struct pii{
	int val,u;
	bool operator<(const pii& b)const{
		return val<b.val||val==b.val&&dep[u]>dep[b.u];
	}
}low[N];
listit next(listit x){
	if(std::next(x)==c.end()) return c.begin();
	else return std::next(x);
}
void findc(int top){
	static int q[N];
	int head=0,tail=0;
	for(int u:c){
		if(u==top) continue;
		q[++tail]=back[u];
		printf(">> %d %d\n",u,back[u]);
	}
	while(head<tail){
		int x=q[++head];
		if(!x||vis[x]) continue;
		printf(">>> %d\n",x);
		listit las;ear.clear();
		while(!vis[x]) ear+=x,vis[x]=1,x=fa[x];
		assert(vis[fa[x]]);
		if(next(cit[x])==cit[fa[x]]) std::reverse(ALL(ear)),las=cit[x];
		else assert(next(cit[fa[x]])==cit[x]),las=cit[fa[x]];
		for(int x:ear){
			las=cit[x]=c.insert(++las,x);
			q[++tail]=back[x];
		}
	}
//	for(int i:bcc)
//		if(!vis[i]&&vis[fa[i]]&&back[i]){
//			int x=back[i];
//			ear.clear();
//			while(x!=fa[i]) ear+=x,x=fa[x];
///			listit las;
//			if(next(cit[fa[i]])==cit[fa[fa[i]]])
//				std::reverse(ALL(ear)),las=cit[fa[i]];
//			else
//				assert(next(cit[fa[fa[i]]])==cit[fa[i]]),las=cit[fa[fa[i]]];
////			printf("EAR: ");for(int i:ear) printf("%d ",i);puts("");
////			printf("%d\n",*las);
////			printc();
//			for(int x:ear) las=cit[x]=c.insert(++las,x);
////			printf(">> ");printc();
//		}
}
int siz[N];
int dir[N];
void tarjan(int u){
//	printf(">>> %d\n",u);
	dfn[u]=++dfc;low[u]={dfc,u};
	dep[sta[++top]=u]=dep[fa[u]]+1;
	siz[dfsta[dep[u]]=u]=1;
	for(int v:G[u]){
		if(v==fa[u]) continue;
		if(dfn[v]){
			low[u]=std::min(low[u],{dfn[v],u});
			if(dfn[v]>dfn[u]) continue;//forward edge
			if(!dir[u]||dep[v]<dep[dir[u]]) dir[u]=v;
			int x=dfsta[dep[v]+1];
//			printf("%d~%d->%d~%d\n",fa[u],u,v,x);
			assert(x!=u);
			if(dep[u]>dep[back[x]]) back[x]=u;
			continue;
		}
		fa[v]=u;tarjan(v);siz[u]+=siz[v];
		low[u]=std::min(low[u],low[v]);
		if(low[v].val<dfn[u]) continue;
		if(low[v].val>dfn[u]){
			T[u]+=v;top--;
			continue;
		}
		assert(low[v].u==back[v]);
		bcc.clear();
		do{bcc+=sta[top];
		}while(sta[top--]!=v);
		assert(sta[top]==u);
		bcc+=u;
		int x=low[v].u;
		for(int i:bcc) in[i]=1,vis[i]=0;
		c.clear();
		while(x!=fa[u]) c.push_back(x),vis[x]=1,x=fa[x];
		std::reverse(ALL(c));
		 printbcc();printc();
		for(auto i=c.begin();i!=c.end();i++) cit[*i]=i;
		back[v]=0;
		for(int i:bcc){
			if(vis[i]) continue;
			if(dfn[v]<dfn[i]&&dfn[i]<dfn[v]+siz[v]&&dir[v]==u)
				if(dep[i]>dep[back[v]]) back[v]=i;
		}
		findc(u);
		T[++_n].clear();
		for(int i:c){
			if(i==u) T[i]+=_n;
			else T[_n]+=i;
		}
		printc();
		for(int i:bcc) in[i]=vis[i]=0;
	}
}
int rt[N],rtc,cur;
int f[N],n;
void calcf(int u){
	for(int v:T[u]) calcf(v);//,printf("%d -> %d\n",u,v);
	if(T[u].empty()) f[u]=u;
	else if(u<=n){
		std::sort(ALL(T[u]),[](int x,int y){return f[x]<f[y];}),
		f[u]=std::min(f[T[u].front()],u);
	}
	else{
		if(f[T[u].back()]<f[T[u].front()]) std::reverse(ALL(T[u]));
		f[u]=f[T[u].front()];
	}
//	printf("f[%d] = %d\n",u,f[u]);
}
void dfs(int u){
	bool pu=u>n;
	for(int v:T[u]){
		if(!pu&&u<f[v]){
			while(cur<rtc&&f[rt[cur+1]]<u) dfs(rt[++cur]);
			printf("%d ",u),pu=1;
		}
		while(cur<rtc&&f[rt[cur+1]]<f[v]) dfs(rt[++cur]);
		dfs(v);
	}
	if(!pu){
		while(cur<rtc&&f[rt[cur+1]]<u) dfs(rt[++cur]);
		printf("%d ",u);
	}
}
int main(){
	freopen("gra.txt","r",stdin);
	int c,TestCase;scanf("%d%d",&c,&TestCase);
	while(TestCase--){
		int m;scanf("%d%d",&n,&m);_n=n;//printf("%d %d\n",n,m);
		for(int i=1;i<=n;i++) G[i].clear(),T[i].clear();
		for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u]+=v,G[v]+=u;//,printf("%d %d\n",u,v);
		dfc=top=0;std::fill(dfn+1,dfn+n+1,0);std::fill(back+1,back+n+1,0);std::fill(dir+1,dir+n+1,0);
		rtc=0;for(int i=1;i<=n;i++) if(!dfn[i]) fa[i]=0,tarjan(rt[++rtc]=i),calcf(i);
		for(cur=1;cur<=rtc;cur++) dfs(rt[cur]);
		puts("");
	}
}
