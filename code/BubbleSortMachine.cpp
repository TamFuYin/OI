#include<bits/stdc++.h>
#include<bits/extc++.h>
std::vector<std::pair<int,int> > q[N];
__gnu_pbds::tree<int> S;
int ans[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	int Q;scanf("%d",&Q);
	int T=0,id=0;
	while(Q--){
		int opt,l,r;scanf("%d",&opt);
		if(opt==1) ++T;
		else scanf("%d%d",&l,&r),
		q[r].emplace_back(T,++id),
		q[l-1].emplace_back(T,-id),
		ans[id]=
	}
	for(int i=1;i<=n;i++){
		S.insert(a[i]);
		for(auto p:q[i]){
			int id=std::abs(p.second),
			k=p.second>0?1:-1;
			ans[id]+=k*S.find_by_order(p.first);
		}
	}
}