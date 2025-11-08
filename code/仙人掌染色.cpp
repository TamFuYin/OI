#include<bits/stdc++.h>
template<typename _T>void ckmin(_T& a,_T b){a=std::min(a,b);}
template<typename _T>void ckmax(_T& a,_T b){a=std::max(a,b);}
#define fi first
#define se second
#define REP(i,l,r) for(int i=int(l);i<=int(r);i++)
const int N=4e5+10;
using ll=long long;
const ll INF=2e18;
using pii=std::pair<int,int>;
using pli=std::pair<ll,int>;
std::basic_string<int> G[N],T[N];
std::map<pii,int> E;
int nt;
int sta[N],top,dfn[N],low[N],dfncnt;
void build(int u,int fa=0){
	sta[++top]=u;
	low[u]=dfn[u]=++dfncnt;
	for(int v:G[u]){
		if(v==fa) continue;
		if(dfn[v]){
			ckmin(low[u],dfn[v]);
		}
		else{
			build(v,u);
			ckmin(low[u],low[v]);
			if(low[v]==dfn[u]){
				T[u]+=++nt;
				do{T[nt]+=sta[top];
				}while(sta[top--]!=v);
			}
			else if(low[v]>dfn[u]){
				T[u]+=v;
				while(sta[top--]!=v);
			}
		}
	}
}
int n;
ll f[N][3];
std::priority_queue<pli> Q[3][3];
int cur[N];
int p;
int deg[N];
void dfs(int u,int fa=0){
	for(int v:T[u])//printf("%d %d\n",u,v),
	dfs(v,u);
	if(u>n){
		ll g[2][2],_g[2];
		assert(E.find({fa,T[u][0]})!=E.end());
		assert(E.find({fa,*--T[u].end()})!=E.end());
		REP(i,0,1) g[i][i]=-i*E[{fa,T[u][0]}],g[i][!i]=-INF;
		REP(k,0,1) REP(l,0,T[u].size()-1){
			int v=T[u][l],nx=l==T[u].size()-1?fa:T[u][l+1];
			assert(E.find({v,nx})!=E.end());
			std::fill(_g,_g+2,-INF);
			REP(i,0,1) REP(j,0,1)
				ckmax(_g[j],g[k][i]+f[v][i+j]-j*E[{v,nx}]);
			std::copy(_g,_g+2,g[k]);
			// printf("g[%d]: ",k);
			// REP(i,0,1) printf("%lld ",g[k][i]);puts("");
		}
		REP(i,0,1) REP(j,0,1) ckmax(f[u][i+j],g[i][j]);
	}
	else{
		auto cal=[n=deg[u]](int b){
			assert(b<=n);
			return 1ll*n*b*(n-b)/2*p;
		};
		int e=fa==0?0:(fa<=n?1:2);
		// fprintf(stderr,">> u=%d deg[u]=%d e=%d\n",u,deg[u],e);
		REP(in,0,e){
			int b=in;ll sum=0;ll& ans=f[u][in];
			assert(b<=deg[u]);
			for(int i=0;i<=2;i++)
				for(int j=0;j<=2;j++)
					while(!Q[i][j].empty())
						Q[i][j].pop();
			for(int v:T[u]) sum+=f[v][0],cur[v]=0,
			Q[0][1].emplace(f[v][1]-f[v][0],v),
			Q[0][2].emplace(f[v][2]-f[v][0],v);
			ans=sum+cal(b);
			while(b-in<deg[u]-e){
				for(int i=0;i<=2;i++)
					for(int j=0;j<=2;j++)
						if(i!=j) while(!Q[i][j].empty()&&cur[Q[i][j].top().se]!=i) Q[i][j].pop();
				std::pair<ll,pii> p;p.fi=-INF;
				for(int i=0;i<2;i++) if(!Q[i][i+1].empty()) ckmax(p,{Q[i][i+1].top().fi,pii{i,i+1}});
				if(!Q[0][2].empty()) for(int i=1;i<=2;i++)
					if(!Q[i][i-1].empty()) ckmax(p,{Q[0][2].top().fi+Q[i][i-1].top().fi,pii{i,i-1}});
				assert(p.fi!=-INF);
				int fr=p.se.fi,to=p.se.se,v=Q[fr][to].top().se;Q[fr][to].pop();
				assert(cur[v]==fr);cur[v]=to;
				for(int i=0;i<=2;i++)
					if(to!=i) Q[to][i].emplace(f[v][i]-f[v][to],v);
				// fprintf(stderr,"fr=%d to=%d v=%d\n",fr,to,v);
				if(to<fr){
					v=Q[0][2].top().se;Q[0][2].pop();
					assert(cur[v]==0);cur[v]=2;
					Q[2][1].emplace(f[v][1]-f[v][2],v);
				}
				sum+=p.fi;
				ckmax(ans,sum+cal(++b));
			}
			for(int v:T[u]) /*fprintf(stderr,"%d ",cur[v]),*/assert(cur[v]==1+(v>n));//fprintf(stderr,"\n");
			if(in&&fa<=n) assert(E.find({fa,u})!=E.end()),ans-=E[{fa,u}];
		}
	}
//	REP(i,0,2)
//		if(f[u][i]>-INF/2)
//			fprintf(stderr,"f[%d,%d]=%lld\n",u,i,f[u][i]);
}
int main(){
	REP(i,0,N-1) REP(j,0,2) f[i][j]=-INF;
	 // freopen(".in","r",stdin);
//	 freopen(".out","w",stdout);
	int m;scanf("%d%d%d",&n,&m,&p);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),
		G[u]+=v,G[v]+=u,
		E[{u,v}]=E[{v,u}]=w,
		++deg[u],++deg[v];
	nt=n;
	build(1);
	dfs(1);
	printf("%lld",f[1][0]);
}
