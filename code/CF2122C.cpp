#include<bits/stdc++.h>
const int N=2e5+10;
std::pair<int,int> x[N],y[N];
bool xl[N],yl[N];
std::vector<int> a[2][2];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&x[i].first,&y[i].first),
			x[i].second=y[i].second=i;
		std::sort(x+1,x+n+1);
		std::sort(y+1,y+n+1);
		std::fill(xl+1,xl+n+1,0);
		std::fill(yl+1,yl+n+1,0);
		for(int i=1;i<=n/2;i++)
			xl[x[i].second]=yl[y[i].second]=1;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				a[i][j].clear();
		for(int i=1;i<=n;i++)
			a[xl[i]][yl[i]].push_back(i);
		assert(a[0][0].size()==a[1][1].size());
		assert(a[0][1].size()==a[1][0].size());
		for(int i=0;i<a[0][0].size();i++)
			printf("%d %d\n",a[0][0][i],a[1][1][i]);
		for(int i=0;i<a[1][0].size();i++)
			printf("%d %d\n",a[1][0][i],a[0][1][i]);
	}
}
