#include<bits/stdc++.h>
const int N=2e5+10;
int a[N];
int left[N],right[N],len[N];
std::set<std::pair<int,int> > S;
using ll=long long;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		S.clear();
		int n;scanf("%d",&n);
		int las=0;
		a[0]=a[n+1]=2e9;
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);
			if(a[i]!=a[i-1]){
				left[i]=las;
				right[las]=i;
				len[las=i]=1;
			}
			else ++len[las];
		}
		right[las]=n+1,left[n+1]=las;
		for(int u=right[0];u!=n+1;u=right[u])
			S.emplace(a[u],u);
		ll ans=0;
		while(S.size()>1||S.size()==1&&len[S.begin()->second]!=1){
			int u=S.begin()->second;S.erase(S.begin());
//			printf(">>> left=%d(%d) right=%d(%d) self=%d(%d)\n",a[left[u]],len[left[u]],a[right[u]],len[right[u]],a[u],len[u]);
			if(len[u]==1){
				int mn=std::min(a[left[u]],a[right[u]]);
				ans+=mn-a[u];a[u]=mn;
			}
			else{
				if(len[u]&1) ++len[u],++ans;
				len[u]/=2,++a[u];
			}
			if(a[u]==a[left[u]]){
				len[u]+=len[left[u]];
				S.erase({a[left[u]],left[u]});
				right[left[left[u]]]=u;
				left[u]=left[left[u]];
			}
			if(a[u]==a[right[u]]){
				len[u]+=len[right[u]];
				S.erase({a[right[u]],right[u]});
				left[right[right[u]]]=u;
				right[u]=right[right[u]];
			}
			S.emplace(a[u],u);
		}
		printf("%lld\n",ans);
	}
}
