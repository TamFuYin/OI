#include<bits/stdc++.h>
#define tfx(x) (x&1?-1:1)
const int N=1e6+10,MOD=998244353;
int a[N],f[N],pre[N],suf[N];
void CDQ(int l,int r){
	if(l==r) return;
	int mid=l+r>>1;
	CDQ(l,mid);
	for(int i=mid-1,min=a[mid];i>=l;min=std::min(min,a[i--])) pre[i]=tfx(i+1)*1ll*min*f[i]%MOD;
	for(int i=l;i<mid;i++) (pre[i]+=pre[i-1])%=MOD;
	for(int i=mid;i>=l;i--) suf[i]=((i!=mid)*suf[i+1]+tfx(i+1)*f[i])%MOD;
	for(int i=mid+1,j=mid-1,min=a[i];i<=r;min=std::min(min,a[++i])){
		while(j>=l&&a[j+1]>=min) --j;
		(f[i]+=tfx(i)*(1ll*suf[j+1]*min%MOD+(j>=l)*pre[j])%MOD)%=MOD;
	}
	CDQ(mid+1,r);
	// printf("[%d,%d]\n",l,r);
	// for(int i=l;i<=r;i++) printf("%d ",f[i]);puts("");
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	f[0]=1;CDQ(0,n);
	printf("%d",(f[n]%MOD+MOD)%MOD);
}