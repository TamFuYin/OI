#include<bits/stdc++.h>
const int N=5e6+10;
std::bitset<N> isp;
std::vector<int> pr;
int mpf[N];
int sum[N];
std::set<int> vis;
int main(){
	// freopen(".in","r",stdin);
	// freopen("equal.out","w",stdout);
	isp.set();
	for(int i=2;i<N;i++){
		if(isp[i]) pr.push_back(i),mpf[i]=i;
		for(int j:pr){
			if(1ll*i*j>=N) break;
			isp.reset(i*j);
			mpf[i*j]=j;
			if(i%j==0){
				break;
			}
		}
	}
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int ai;scanf("%d",&ai);
			while(ai!=1){
				int c=0,p=mpf[ai];
				while(mpf[ai]==p) ai/=p,++c;
				sum[p]+=c;
				vis.insert(p);
			}
		}
		bool ans=1;
		for(int p:vis){
			// if(sum[p]&1) ans&=(n&1)&&sum[p]-2*max[p]>=siz[p]-2;
			// else ans&=sum[p]-2*max[p]>=0;
			ans&=sum[p]&1^1;
			sum[p]=0;
		}
		vis.clear();
		puts(ans||(n&1)?"Yes":"No");
	}
}
