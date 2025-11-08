#pragma GCC optimize(3)
#include<bits/stdc++.h>
namespace TFX{
	const int N=3e6+10;
	int rnk[N],p[N],r;
	bool vis[N];
	void init(){
		for(int i=2;i<=1e4;i++){
			if(!vis[i]) p[rnk[i]=r++]=i;
			for(int j=0;j<r;j++){
				if(i*p[j]>1e4) break;
				vis[i*p[j]]=1;
				if(i%p[j]==0) break;
			}
		}
	}
	struct number{
		std::bitset<1230> b;
		std::unordered_set<int> s;
		void input(){
			b.reset(),s.clear();
			int k;long long a;std::cin>>k;
			while(k--){
				std::cin>>a;
				if(a<=1e4) b.set(rnk[a]);
				else s.insert(a%114514123);
			}
		}
		bool check(const number& n)const{
			if((b&n.b).any()) return 1;
			if(n.s.size()<s.size()) {for(int i:n.s) if(s.find(i)!=s.end()) return 1;}
			else for(int i:s) if(n.s.find(i)!=n.s.end()) return 1;
			return 0;
		}
		void join(number& n){
			b|=n.b;
			if(n.s.size()<s.size()) for(int i:n.s) s.insert(i);
			else{for(int i:s) n.s.insert(i);std::swap(s,n.s);}
		}
	}sta[N];
	int main(){
		int n;std::cin>>n;
		int top=0;
		for(int i=1;i<=n;i++){
			sta[++top].input();
			while(top>1&&sta[top-1].check(sta[top])) sta[top-1].join(sta[top]),--top;
		}
		return top;
	}
}
int main(){
	freopen("gcd.in","r",stdin);
	freopen("gcd.out","w",stdout);
	TFX::init();std::cin.tie(0),std::ios::sync_with_stdio(0);
	int T,id;std::cin>>T>>id;
	while(T--) std::cout<<TFX::main()<<'\n';
}
