#include<bits/stdc++.h>
const int NM=1e6+10,M=1e5+10;
char s[NM];
int ls0[NM],ls1[NM];
int n,m;
int solve(int l,int r){
	return std::lower_bound(ls0+(r-1)*m,ls0+r*m,l)-ls0-(r-1)*m+
	std::lower_bound(ls1+(r-1)*m,ls1+r*m,l)-ls1-(r-1)*m;
}
#define p(x,y) (x-1)*m+j
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s+(i-1)*m);
		for(int j=0;j<m;j++){
			if(s[p(i,j)]=='1') ls1[p(i,j)]=i,ls0[p(i,j)]=i==1?0:ls0[p(i-1,j)];
			else ls0[p(i,j)]=i,ls1[p(i,j)]=i==1?0:ls1[p(i-1,j)];
		}
	}
	for(int i=1;i<=n;i++){
		std::sort(ls0+(i-1)*m,ls0+i*m);
		std::sort(ls1+(i-1)*m,ls1+i*m);
	}
	int q,x,y,z,a=1,b=n,last;scanf("%d%d%d%d",&q,&x,&y,&z);
	long long ans=0;
	while(q--){
		int l=std::min(a,b),r=std::max(a,b);
		ans+=last=solve(l,r);
		a=(1ll*a*x+1ll*last*y+z)%n+1,b=(1ll*b*y+1ll*last*z+x)%n+1;
	}
	printf("%lld",ans);
}
