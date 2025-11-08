#include<bits/stdc++.h>
struct IO{
	static const int S=1<<21;
	char buf[S],*p1,*p2;int st[105],Top;
	~IO(){clear();}
	inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
	inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
	inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
	template<typename T>inline IO&operator >> (T&x){
		x=0;bool F=0;char ch=gc();
		while(!isdigit(ch)){if(ch=='-') F^=1;ch=gc();}
		while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
		F?x=-x:0;return *this;
	}
	inline IO&operator << (const char c){pc(c);return *this;}
	template<typename T>inline IO&operator << (T x){
		if(x<0) pc('-'),x=-x;
		do{st[++st[0]]=x%10,x/=10;}while(x);
		while(st[0]) pc('0'+st[st[0]--]);return *this;
	}
}fin,fout;
const int N=2e6+10,lgN=std::__lg(N);
std::vector<int> to[N];
const int MOD=998244353;
std::vector<int> vto[N];
int f[N],ans;
std::mt19937 rnd(time(0));
int a[N];
void dfs1(int u,int fa=0){
	for(int v:to[u]){
		if(v==fa) continue;
		dfs1(v,u);
		a[u]^=a[v];
	}
}
void dfs2(int u,int top,int fa=0){
	for(int v:to[u]){
		if(v==fa) continue;
		dfs2(v,a[v]?top:v,u);
		if(!a[v]) vto[top].push_back(v);
	}
}
void solve(int u){
	f[u]=1;
	for(int v:vto[u]){
//		printf("%d %d\n",u,v);
		solve(v);
		f[u]=1ll*f[u]*(f[v]+1)%MOD;
	}
	(ans+=f[u])%=MOD;
}
int main(){
//	freopen("ex_wolf1.in","r",stdin);
//	freopen("wolf.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) fin>>u>>v,
		to[u].push_back(v),to[v].push_back(u);
	for(int i=1,x,y,t;i<=m;i++) fin>>x>>y,t=rnd(),a[x]^=t,a[y]^=t;
	dfs1(1),dfs2(1,1);solve(1);
//	for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
	fout<<ans;
}
