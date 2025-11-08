#include<bits/stdc++.h>
struct point{
	int x,y;
};
const int N=1e4;
struct circle{
	point p;
	int r;
	bool operator<(const circle& c)const{
		return r>c.r;
	}
}c[N];
using ll=long long;
double p2(double x){return x*x;}
std::mt19937 rnd(time(0));
int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&c[i].p.x,&c[i].p.y,&c[i].r);
	std::sort(c+1,c+n+1);
	int T=1e8/(q*n);
	while(q--){
		int x0,y0,dx,dy,cnt=0;scanf("%d%d%d%d",&x0,&y0,&dx,&dy);
		for(int t=T;t;t--){
			double x=x0+1.*rnd()/UINT_MAX*dx,y=y0+1.*rnd()/UINT_MAX*dy;
//			printf("%lf %lf\n",x,y);
			for(int i=1;i<=n;i++)
				if(p2(c[i].p.x-x)+p2(c[i].p.y-y)<=p2(c[i].r))
					goto Continue;
			continue;
			Continue:;++cnt;
		}
		printf("%lf\n",100.0*cnt/T);
	}
}
