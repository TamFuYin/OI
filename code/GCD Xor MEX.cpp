#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=2e5+10,M=2e6;
int a[N];
int mxg[N];
bool wb[N];
int cnt[M];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),++cnt[a[i]];
	std::sort(a+1,a+n+1);
	int mex=0;
	for(int i=1;i<=n;i++)
		if(a[i]==mex) ++mex;
	std::fill(mxg+1,mxg+n+1,-1e9);
	for(int g=2;g<=1e6;g++){
		int tot=0;
		for(int i=g;i<=1e6;i+=g) tot+=cnt[i];
		if(mxg[tot]==g-1) wb[tot]=1;
		else wb[tot]=0;
		mxg[tot]=g;
	}
	for(int i=n-cnt[0]-1;i>=1;i--){
		wb[i]=mxg[i+1]==mxg[i]-1||mxg[i]==mxg[i+1]-1||mxg[i]<=mxg[i+1]&&wb[i+1]||mxg[i]>=mxg[i+1]&&wb[i];
		ckmax(mxg[i],mxg[i+1]);
	}
	for(int k=1;k<=n;k++){
		int ans=std::max(std::min(mex,k)|1,mxg[k]);
		int p=mxg[std::max(k-cnt[0],1)];
		if(wb[std::max(k-cnt[0],1)]&&(p&1)) p|=1;
		else p^=1;
		if(k!=1&&cnt[0]) ans=std::max(ans,p);
		printf("%d ",ans);
	}
}
