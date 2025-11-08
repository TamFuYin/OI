#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=2e5+10;
int n,m,qu;
int a[N],b[N],w[N];
vector<pair<int,int> > nei[N];
int d1[N],dn[N];
int vis[N];
void dij(int st,int d[]){
	for(int i=1;i<=n;i++)d[i]=inf;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	q.push(mp(d[st]=0,st));
	while(q.size()){
		int x=q.top().Y;q.pop();
		if(vis[x])continue;vis[x]=true;
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X,len=w[nei[x][i].Y];
			if(d[x]+len<d[y])d[y]=d[x]+len,q.push(mp(d[y],y));
		}
	}
}
int fa1[N];
vector<int> son1[N],sonn[N];
int ord[N];
bool cmp(int x,int y){return d1[x]<d1[y];}
bool cmp0(int x,int y){return dn[x]<dn[y];}
vector<int> ton;int id[N];
int pre[N],suf[N];
void dfs(int x,int las,int p[],vector<int> vec[]){
	if(~id[x])las=id[x];
	p[x]=las;
	for(int i=0;i<vec[x].size();i++){
		int y=vec[x][i];
		dfs(y,las,p,vec);
	}
}
int del_dis[N];
vector<int> add[N],del[N];
signed main(){
	cin>>n>>m>>qu;
	for(int i=1;i<=m;i++)scanf("%lld%lld%lld",a+i,b+i,w+i),nei[a[i]].pb(mp(b[i],i)),nei[b[i]].pb(mp(a[i],i));
	dij(1,d1),dij(n,dn);
	for(int i=1;i<=n;i++)ord[i]=i;
	sort(ord+1,ord+n+1,cmp);
	for(int _i=2;_i<=n;_i++){
		int i=ord[_i];
		for(int j=0;j<nei[i].size();j++){
			int x=nei[i][j].X,len=w[nei[i][j].Y];
			if(d1[x]+len==d1[i]){fa1[i]=x,son1[x].pb(i);break;}
		}
	}
	int x=n;
	while(true){
//		if(n==2e5)cout<<x<<"!!\n";
		ton.pb(x);
		if(x==1)break;
		x=fa1[x];
	}
	reverse(ton.begin(),ton.end());
	memset(id,-1,sizeof(id));
	for(int i=0;i<ton.size();i++)id[ton[i]]=i;
	dfs(1,-1,pre,son1);
	sort(ord+1,ord+n+1,cmp0);
	for(int _i=2;_i<=n;_i++){
		int i=ord[_i];
		if(~id[i])sonn[ton[id[i]+1]].pb(i);
		else for(int j=0;j<nei[i].size();j++){
			int x=nei[i][j].X,len=w[nei[i][j].Y];
			if(dn[x]+len==dn[i]){sonn[x].pb(i);break;}
		}
	}
	dfs(n,-1,suf,sonn);
	memset(vis,-1,sizeof(vis));
	for(int i=0;i+1<ton.size();i++){
		int x=ton[i],y=ton[i+1];
		for(int j=0;j<nei[x].size();j++){
			int z=nei[x][j].X,len=w[nei[x][j].Y];
			if(z==y&&d1[x]+len==d1[y]){vis[nei[x][j].Y]=i;break;}
		}
	}
	for(int i=1;i<=m;i++)if(!~vis[i]){
		int l=pre[a[i]],r=suf[b[i]],v=d1[a[i]]+w[i]+dn[b[i]];
		if(l<r)add[l].pb(v),del[r].pb(v);
		swap(a[i],b[i]);
		l=pre[a[i]],r=suf[b[i]],v=d1[a[i]]+w[i]+dn[b[i]];
		if(l<r)add[l].pb(v),del[r].pb(v);
	}
	multiset<int> st;
	for(int i=0;i+1<ton.size();i++){
		for(int j=0;j<add[i].size();j++)st.insert(add[i][j]);
		for(int j=0;j<del[i].size();j++)st.erase(st.find(del[i][j]));
		del_dis[i]=st.empty()?inf:*st.begin();
	}
	while(qu--){
		int x,v=inf,ans;
		scanf("%lld",&x);
		if(!~vis[x]) ans=min(d1[n],min(d1[a[x]]+v+dn[b[x]],d1[b[x]]+v+dn[a[x]]));
		else ans=min(d1[n]-w[x]+v,del_dis[vis[x]]);
		if(ans>1e15) puts("-1");
		else printf("%lld\n",ans);
	}
	return 0;
}
