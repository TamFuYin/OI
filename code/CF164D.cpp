#define rep(i,l,r) ((l)<(r)?for(int i=l;i<=r;i++):for(int i=r;i>=l;i--))
#include<bits/stdc++.h>
const int N=1e6;
int n,k,tot;
int row[N],sz[N];
struct DLX{
	int L,R,U,D;
}x[N];
void clear(){
	for(int i=0;i<=n;i++) x[i]={i,i,(i+n)%(n+1),(i+1)%(n+1)},row[i]=i;
	tot=n;
}
void add_col(std::vector<int> v){
	for(int i=0;i<v.size();i++){
		int las=v[(i-1+v.size())%v.size()],nxt=v[(i+1)%v.size()];
		x[++tot]={row[v[i]],v[i],las,nxt};
		row[v[i]]=tot;
	}
}
bool dance(int dep){
	int c=x[0].R;
	if(!c) return true;
	if(dep==k) return false;
}
struct point{
	int x,y;
}a[N];
#define sq(x) (x)*(x)
int dist2(point a,point b){
	return sq(a.x-b.x)+sq(a.y-b.y);
}
std::priority_queue<std::pair<int,int> > pq;
bool check(int mid){
	clear();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(dist2(a[i],a[j])>mid){
				add_col({0,i,j});
			}
	for(int i=1;i<=n;i++) pq.emplace(to[i].size(),i);
	int u=pq.top();pq.pop();
	return dance(0);
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	int left=0,right=1e9;
	while(left<right){
		int mid=left+right>>1;
		if(check(mid)) right=mid;
		else left=mid+1;
	}
	check(left);
	for(int i=1;i<=n;i++) if(e[i]) printf("%d\n",i);
}