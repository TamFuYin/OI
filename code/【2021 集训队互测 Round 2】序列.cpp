#include<bits/stdc++.h>
const int N=24e5+10;
int cnt;
std::map<int,int> S[N];
std::vector<int> to[N];
int dfn[N],low[N];
bool insta[N];
int sta[N],top;
int tot;
int col[N];
void tarjan(int u){
	low[u]=dfn[u]=++dfn[0];
	insta[sta[++top]=u]=1;
	for(int v:to[u]){
		if(!dfn[v]) tarjan(v),low[u]=std::min(low[u],low[v]);
		else if(insta[v]) low[u]=std::min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		++tot;
		do{
			col[sta[top]]=tot;
			insta[sta[top]]=0;
		}while(sta[top--]!=u);
	}
}
bool chsn[N];
int vis[N];
bool judge(int x){
	if(vis[col[x]])
		return 1;
	if(vis[col[x^1]])
		return 0;
	if(col[x]<col[x^1]){
		vis[col[x]]=1;
		return 1;
	}
	else{
		vis[col[x^1]]=1;
		return 0;
	}
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	while(m--){
		int a[3],x;
		scanf("%d%d%d%d",a,a+1,a+2,&x);
		for(int i=0;i<3;i++){
			if(S[a[i]].find(x)==S[a[i]].end()) S[a[i]][x]=cnt++,cnt++;
			if(S[a[i]].find(x+1)==S[a[i]].end()) S[a[i]][x+1]=cnt++,cnt++;
		}
		for(int i=0;i<3;i++){
			int u=a[i],v=a[(i+1)%3],w=a[(i+2)%3];
			to[S[u][x]^1].push_back(S[v][x]);
			to[S[u][x]^1].push_back(S[w][x]);
			to[S[u][x+1]].push_back(S[v][x+1]^1);
			to[S[u][x+1]].push_back(S[w][x+1]^1);
		}
	}
	for(int u=1;u<=n;u++)
		if(S[u].size()>1)
			for(auto i=S[u].begin(),j=++S[u].begin();j!=S[u].end();i=j++)
				to[j->second].push_back(i->second),
				to[i->second^1].push_back(j->second^1);
	for(int i=0;i<cnt;i++) if(!dfn[i]) tarjan(i);
	for(int i=0;i<cnt;i+=2)
		if(col[i]==col[i+1]){
			puts("NO");
			return 0;
		}
	puts("YES");
	for(int u=1;u<=n;u++){
		if(S[u].empty()){
			printf("114514 ");
			continue;
		}
		auto it=S[u].begin();
		while(it!=S[u].end()&&judge(it->second)) ++it;
		printf("%d ",std::prev(it)->first);
//		while(it!=S[u].end()) assert(!judge(it->second)),++it;
	}
}
