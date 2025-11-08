#include<bits/stdc++.h>
int n2;
const int N=5e3+10,N2=N*2;
std::vector<int> to[N];
int fa[N2],mp[N];
int build(int l,int r){
	int o=++n2;
	if(l==r){
		mp[l]=o;
		return o;
	}
	int mid;scanf("%d",&mid);
	int x=build(l,mid),y=build(mid+1,r);
	fa[x]=fa[y]=o;
	return o;
}
int n,ind[N],tp[N];
std::queue<int> Q;
void topo(){
	for(int u=1;u<=n;u++)
		for(int v:to[u])
			++ind[v];
	for(int u=1;u<=n;u++)
		if(!ind[u]) Q.push(u);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		tp[++tp[0]]=u;
		for(int v:to[u]){
			if(!--ind[v])
				Q.push(v);
		}
	}
}
int cnt[N][N2],one[N][N2];
int ans[N];
void insert(int u){
	int x=mp[u];
	while(x){
		cnt[u][x]=1;
		--ans[one[u][x]=u];
		++ans[0];
		x=fa[x];
	}
}
void combine(int u,int v){
	for(int i=1;i<=n2;i++){
		if(cnt[u][i]&&cnt[v][i]){
			++ans[0];
			if(cnt[u][i]==1) --ans[one[u][i]];
			if(cnt[v][i]==1&&one[v][i]!=one[u][i]) --ans[one[v][i]];
			if(one[u][i]!=one[v][i]) cnt[u][i]+=cnt[v][i];
			if(cnt[u][i]==1) one[u][i]|=one[v][i];
			else one[u][i]=0;
		}
		else{
			cnt[u][i]|=cnt[v][i],
			one[u][i]|=one[v][i];
		}
	}
}
int main(){
	freopen("dag.in","r",stdin);
	freopen("dag.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v);
	build(1,n);topo();
	for(int i=n;i>=1;i--){
		int u=tp[i];
		insert(u);
		for(int v:to[u]){
			combine(u,v);
		}
	}
	printf("%d\n",ans[0]);
	for(int i=1;i<=n;i++) printf("%d ",ans[0]+ans[i]);
}
