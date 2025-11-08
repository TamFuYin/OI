#include<bits/stdc++.h>
const int N=1e5+10;
std::vector<int> to[N*2];
namespace SAM{
	int next[N*2][26],link[N*2],len[N*2],last,tot;
	int ep[N*2],occ[N*2];
	void init(int n){
		memset(next,0,sizeof(int)*26*n);
		memset(link,0,sizeof(int)*n);
		memset(ep,0,sizeof(int)*n);
		memset(occ,0,sizeof(int)*n);
		tot=0;link[0]=-1;len[0]=0;last=0;
	}
	void insert(int c,int pos){
		int cur=++tot;
		ep[cur]=pos;occ[cur]=1;
		len[cur]=len[last]+1;
		int p=last;last=cur;
		while(~p&&!next[p][c])
			next[p][c]=cur,
			p=link[p];
		if(!~p){
			link[cur]=0;
			return;
		}
		int q=next[p][c];
		if(len[q]==len[p]+1){
			link[cur]=q;
			return;
		}
		int cl=++tot;
		ep[cl]=ep[q];
		len[cl]=len[p]+1;
		link[cl]=link[q];
		link[q]=link[cur]=cl;
		memcpy(next[cl],next[q],sizeof(int)*26);
		while(~p&&next[p][c]==q) next[p][c]=cl,p=link[p];
	}
	void make(){
		for(int i=0;i<=tot;i++) to[i].clear();
		for(int i=1;i<=tot;i++) to[link[i]].push_back(i);
		for(int i=tot;i>=1;i--) occ[link[i]]+=occ[i];
	}
	int val(int u,int l){
		return std::max(len[u]-std::max(l,len[link[u]]),0)*occ[u];
	}
}
int n;
namespace seg{
	int rt[N*2];
	int ls[N*4],rs[N*4],tot;
	int mnd[N*4]={INT_MAX},mxd[N*4],las[N*4],lsp[N*4];
	void pushup(int p){
		mnd[p]=std::min(mnd[ls[p]],mnd[rs[p]]);
		mxd[p]=std::max(mxd[ls[p]],mxd[rs[p]]);
		las[p]=rs[p]?las[rs[p]]:las[ls[p]];
		lsp[p]=rs[p]?lsp[rs[p]]:lsp[ls[p]];
	}
	std::vector<std::pair<int*,int> > upd;
	std::vector<std::pair<bool,int> > dig;
	std::vector<std::pair<int,int> > cmb;
	int topupd[N],topdig[N],topcmb[N];
	void record(int u){
		topupd[u]=upd.size();
		topdig[u]=dig.size();
		topcmb[u]=cmb.size();
	}
	bool del[N];
	bool modify(int p,int x,int l=1,int r=n){
		if(!p||las[p]>x) return 0;
		if(l==r){
			mxd[p]=mnd[p]=x-l;
			lsp[p]=x;
			return 1;
		}
		int mid=l+r>>1;
		return modify(rs[p],x,mid+1,r)||modify(ls[p],x,l,mid);
	}
	std::pair<bool,bool> rollback(int u,int v){
		while(upd.size()!=topupd[v]){
			if(!del[upd.back().second])
				*upd.back().first=upd.back().second;
			upd.pop_back();
		}
		while(cmb.size()!=topcmb[v]){
			int x=cmb.back().first,y=cmb.back().second;
			if(!del[y]) del[y]=del[x],mnd[y]=mnd[x],mxd[y]=mxd[x],las[y]=las[x],lsp[y]=lsp[x];
			cmb.pop_back();
		}
		bool a[2]={1,1};
		while(dig.size()!=topdig[v]){
			bool x=dig.back().first;
			int y=lsp[dig.back().second];
			if(y) a[x]&=modify(x?rt[u]:rt[v],y);//,printf("DIG %d %d\n",x,y);
			dig.pop_back();
		}
		return {a[0],a[1]};
	}
	int newnode(){
		++tot;
		ls[tot]=rs[tot]=del[tot]=0;
		return tot;
	}
	void insert(int& p,int x,int l=1,int r=n){
		if(!p) p=newnode();
		if(l==r){
			mnd[p]=mxd[p]=0,las[p]=lsp[p]=l;
			return;
		}
		int mid=l+r>>1;
		if(x<=mid) insert(ls[p],x,l,mid);
		else insert(rs[p],x,mid+1,r);
		pushup(p);
	}
	void merge(int& u,int v){
		if(!v) return dig.emplace_back(0,u);
		if(!u) return upd.emplace_back(&u,u),u=v,dig.emplace_back(1,v);
		cmb.emplace_back(u,v);
		merge(ls[u],ls[v]),merge(rs[u],rs[v]);
		pushup(u);
	}
	void update(int& p,int k,int l=1,int r=n){
		if(mnd[p]+1>k) return;
		if(l==r){
			del[p]=1,p=0;
			return;
		}
		int mid=l+r>>1;
		update(ls[p],k,l,mid);
		update(rs[p],k,mid+1,r);
		if(!ls[p]&&!rs[p]){del[p]=1,p=0;return;}
		pushup(p);
	}
	void init(){
		tot=0;
		std::fill(rt+1,rt+SAM::tot+1,0);
	}
}
int ans;
char s[N];
namespace bf{
	bool a[N];
	std::vector<int> ep[N];
	void init(){
		memset(a,0,sizeof a);
		for(int i=0;i<=SAM::tot;i++) ep[i].clear();
	}
	void dfs(int u){
		if(SAM::ep[u]) ep[u].push_back(SAM::ep[u]);
		for(int v:to[u])
			dfs(v),ep[u].insert(ep[u].end(),ep[v].begin(),ep[v].end());
		std::sort(ep[u].begin(),ep[u].end());
	}
	void solve(int u){
		std::vector<int> cv;
//		printf("%d(%d):",u,SAM::len[u]);
		for(int i=1;i<ep[u][0];i++) if(!a[i]) return;
		int mx=0;
		for(int i=0;i<ep[u].size();i++){
			int p=ep[u][i],nx=i==ep[u].size()-1?n+1:ep[u][i+1],f=0;
			for(int j=nx-1;j>=p;j--) if(!a[j]) {f=j;break;}
			if(f) mx=std::max(mx,f-p);
		}
		for(int i:ep[u]){
//			printf("%d,",i);
			for(int j=i;j<i+SAM::len[u];j++)
				if(!a[j]) a[j]=1,cv.push_back(j);
		}
//		printf("\n%d %d \n",mx,SAM::val(u,mx));
		ans+=SAM::val(u,mx);
//		puts(s+1);
//		for(int i=1;i<=n;i++) printf("%d",(int)a[i]);puts("");
		for(int v:to[u])
//		printf("%d->%d\n",u,v),
		solve(v);
		for(int i:cv) a[i]=0;
	}
}
void dfs(int u){
	if(SAM::ep[u]) seg::insert(seg::rt[u],SAM::ep[u]);
	for(int v:to[u]){
		dfs(v);
		seg::merge(seg::rt[u],seg::rt[v]);
		seg::record(v);
	}
}
void solve(int u,bool fea=1){
	if(SAM::len[u]&&fea){
		// printf("%d %d\n",SAM::len[u],seg::mxd[seg::rt[u]]);
		ans+=SAM::val(u,seg::mxd[seg::rt[u]]);
		seg::update(seg::rt[u],SAM::len[u]);
	}
	std::reverse(to[u].begin(),to[u].end());
	for(int v:to[u]){
		auto p=seg::rollback(u,v);
		// printf("ROLLBACK %d %d %d%d\n",u,v,(int)p.first,(int)p.second);
		solve(v,fea&p.second);
		fea&=p.first;
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		SAM::init(n*2+1);
		for(int i=n;i>=1;i--) SAM::insert(s[i]-'a',i);
		SAM::make();
		ans=0;
//		bf::init(),
//		bf::dfs(0),
//		bf::solve(0);
		seg::init(),
		dfs(0),
		solve(0);
		printf("%d\n",ans);
	}
}
/*
input:
4
aaaa
abbaabba
abaababa
qingyuislittlecyanfish

output:
10
8
13
1
*/