#include<bits/stdc++.h>
const int N=1e5+10;
int s[N];
int a[N],b[N];
int main(){
	for(int i=0;i<(1<<6);i++){
		if(__builtin_popcount(i)==3) s[++s[0]]=i;
	}
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		if(r-l+1>=48) {puts("YES");continue;}
		for(int i=l;i<=r;i++) b[i-l]=a[i];
		int m=r-l+1;bool yes=0;
		std::sort(b,b+m);
		for(int i=0;i<m-2;i++)
		if(b[i]+b[i+1]>b[i+2]){
			for(int j=i+4;j<m-2;j++)
			if(b[j]+b[j+1]>b[j+2]){
				yes=1;break;
			}
			if(yes) break;
		}
		if(yes) {puts("YES");continue;}
		for(int i=0;i<m-5;i++){
			int c[4],d[4];
			for(int j=1;j<=s[0];j++){
				c[0]=d[0]=0;
				for(int k=0;k<6;k++){
					if(s[j]&1<<k) c[++c[0]]=b[i+k];
					else d[++d[0]]=b[i+k];
				}
				if(c[1]+c[2]>c[3]&&d[1]+d[2]>d[3]){
					yes=1;break;
				}
			}
			if(yes) break;
		}
		if(yes) {puts("YES");continue;}
		puts("NO");
	}
}
