#include<bits/stdc++.h>
const int N=1e5;
struct point{
	int x,y;
	bool operator<(const point& b)const{
		return x<b.x;
	}
}a[N];
struct question{
	int xl,xr,yl,yr;
	bool operator<(const question& b)const{
		return bl[xl]<bl[b.xl]||bl[xl]==bl[b.xl]&&xr<b.xr;
	}
}b[N];
int lsh[N];
#define lshrk(x) std::lower_bound(lsh+1,lsh+lsh[0]+1,x)-lsh
std::vector<int> xve[N];
int main(){
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y),lsh[++lsh[0]]=a[i].x;
	for(int i=1;i<=q;i++) scanf("%d%d%d%d",&b[i].xl,&b[i].xr,&b[i].yl,&b[i].yr),
	lsh[++lsh[0]]=b[i].xl,lsh[++lsh[0]]=b[i].xr;
	std::sort(lsh+1,lsh+lsh[0]+1);
	lsh[0]=std::unique(lsh+1,lsh+lsh[0]+1)-lsh;
	int l=1,r=0;
	for(int i=1;i<=n;i++) xve[lshrk(a[i].x)].push_back(i);
	for(int i=1;i<=q;i++) b[i].xl=lshrk(b[i].xl),b[i].xr=lshrk(b[i].xr);
	int B=sqrt(lsh[0]);
	for(int i=1;i<=lsh[0];i++) bl[i]=(i-1)/B;
	std::sort(b+1,b+q+1);
	for(int i=1;i<=q;i++){
		for(;r<b[i].xr;r++) for(int j:xve[r+1]) ins(j);
		for(;l>b[i].xl;l--) for(int j:xve[l-1]) ins(j);
		for(;r>b[i].xr;r--) for(int j:xve[r-1]) del(j);
		for(;r>b[i].xr;r--) for(int j:xve[r-1]) del(j);
	}
}