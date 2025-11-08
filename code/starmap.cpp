#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
#include<bits/stdc++.h>
namespace TFX{
	const int N=2e5+10;
	using vi=std::vector<int>;
	vi to[N];
#define add(u,v) to[u].push_back(v)
	int siz[N],hs[N];
	void makeTree(int u,int fa=0){
		siz[u]=1;
		for(int v:to[u]){
			if(v==fa) continue;
			makeTree(v,u),
			siz[u]+=siz[v];
			if(siz[v]>siz[hs[u]]) hs[u]=v;
		}
	}
	using a2=std::array<int,2>;
	a2 getCentr(int n){
		a2 ret{0,0};
		for(int i=1;i<=n;i++){
			if(std::max(siz[hs[i]],n-siz[i])<=n/2)
				ret[!!ret[0]]=i;
		}
		return ret;
	}
	vi bfs(int s,int s_fa=0){
		static vi ret;ret.clear();
		static int fa[N],q[N];
		int head=0,tail=1;
		fa[q[1]=s]=s_fa;
		while(head<tail){
			int u=q[++head];
			ret.push_back(u);
			for(int v:to[u]){
				if(v==fa[u]) continue;
				fa[q[++tail]=v]=u;
			}
		}
		return ret;
	}
	vi ans;
	int cur;
	void push_ans(vi& a,int t=1){
		while(t--){
			assert(!a.empty());
//			printf("push_ans %d\n",a.back());
			ans.push_back(a.back()),a.pop_back();
			--cur;
		}
	}
	void push_ans(int a){
//		printf("push_ans %d\n",a);
		ans.push_back(a),--cur;
	}
	int avoid(int x,int y){
		assert(to[x].size()==2);
		return to[x][to[x][0]==y];
	}
	int cntChain(int u,int fa){
		if(to[u].size()!=2) return 0;
		return cntChain(avoid(u,fa),u)+1;
	}
	vi v0,v1;
	void clear(int n){
		for(int i=1;i<=n;i++) to[i].clear();
		ans.clear();v0.clear();v1.clear();
		std::fill(hs+1,hs+n+1,0);
	}
	char s[N];
	int n;
	bool solve(){
		if(n<=2){
			for(int i=1;i<=n;i++) ans.push_back(i);
			return n==1&&s[1]=='1'||n==2&&s[1]=='1'&&s[2]=='0';
		}
		for(int i=1;i<=n;i+=2) if(s[i]!='1') return 0;
		if(s[2]!='0') return 0;
		cur=n;makeTree(1);
		a2 c=getCentr(n);
		if(c[1]&&s[n]!='0') return 0;
		if(to[c[0]].size()==2&&c[1]) std::swap(c[0],c[1]);
		if(to[c[0]].size()==2){
			if(!c[1]){
				int x=to[c[0]][0],y=to[c[0]][1];
				if(cntChain(x,c[0])>cntChain(y,c[0])) std::swap(x,y);
				v1=bfs(y,c[0]);
				assert(n&1);
				push_ans(c[0]);
				c={x,c[0]};
				if(s[cur]!='0') return 0;
			}
			else{
				if(cntChain(c[0],c[1])>cntChain(c[1],c[0])) std::swap(c[0],c[1]);
				v1=bfs(c[1],c[0]);
			}
			int t=cntChain(c[0],c[1]);
//			printf("%d %d %d\n",c[0],c[1],t);
			while(t--){
//				putchar('(');
				push_ans(v1),push_ans(c[0]);
				c={avoid(c[0],c[1]),c[0]};
				if(s[cur]!='0') return 0;
//				putchar(')');
			}
		}
		else{
			if(!c[1]) makeTree(c[0]),c[1]=hs[c[0]];
			v1=bfs(c[1],c[0]);
		}
//		printf("%d %d\n",c[0],c[1]);
		v0=bfs(c[0],c[1]);
		int d=v0.size()-v1.size();
		bool last=s[cur-d]-'0';
//		printf("last=%d d=%d\n",last,d);
		if(last==0) push_ans(v0,d);
		else{
			if(!d) return 0;
			push_ans(v0,d-1),push_ans(v1);
		}
//		printf("cur=%d\n",cur);
		if(std::find(s+cur+1,s+cur+d+1,'0')!=s+cur+d+1) return 0;
		while(cur>2){
//			puts("(");
			if(s[cur-2]-'0'==last) push_ans(v0),push_ans(v1);
			else push_ans(last?v0:v1,2);
			last=s[cur]-'0';
//			puts(")");
		}
		assert(cur==2);
		push_ans(v0),push_ans(v1);
		return 1;
	}
	void main([[maybe_unused]]int TEST_CASE){
		scanf("%d",&n);//printf("%d\n",n);
		clear(n);
		for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);//,printf("%d %d\n",u,v);
		scanf("%s",s+1);//printf("%s\n",s+1);
		if(solve()){
			puts("YES");
//			assert(ans.size()==n);
			while(!ans.empty()) printf("%d ",ans.back()),ans.pop_back();puts("");
		}
		else puts("NO");
	}
}
int main(){
//	freopen("starmap3.in","r",stdin);
//	freopen("starmap3.out","w",stdout);
	int T,O;scanf("%d%d",&T,&O);
	while(T--) TFX::main(O);
}
