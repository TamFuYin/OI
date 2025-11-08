#include<bits/stdc++.h>
#define _assert(x) ({if(!(x)) printf("Assertion failed: %s, LINE=%d\n",#x,__LINE__);})
const int N=1e6+10;
int b,a[N];
struct operate{
	int op,l,r,x;
}o[N];
int sz[N],pa[N];
int findp(int x){
	return pa[x]==x?x:pa[x]=findp(pa[x]);
}
int rt[N];
int ans[N];
int tag,max;
void rebuild(int L,int R){
	tag=0,max=*std::max_element(a+L,a+R+1);
	std::fill(sz+L,sz+R+1,0),std::iota(pa+L,pa+R+1,L);
	for(int i=L;i<=R;i++){
		if(!rt[a[i]]) rt[a[i]]=i;
		else pa[i]=rt[a[i]];
		sz[rt[a[i]]]++;
	}
}
int m;
void solve(int L,int R){
	rebuild(L,R);
	for(int t=1;t<=m;t++){
		int op=o[t].op,l=std::max(o[t].l,L),r=std::min(o[t].r,R),x=o[t].x;
		if(L==l&&r==R){
			if(op==1){
				if(2*x+tag<=max){
					for(int i=tag+1;i<=x+tag;i++) if(rt[i]){
						if(!rt[i+x]) a[rt[i+x]=rt[i]]+=x;
						else pa[rt[i]]=rt[i+x],sz[rt[i+x]]+=sz[rt[i]];
						rt[i]=0;
					}
					tag+=x;
				}
				else{
					for(int i=x+tag+1;i<=max;i++) if(rt[i]){
						if(!rt[i-x]) a[rt[i-x]=rt[i]]-=x;
						else pa[rt[i]]=rt[i-x],sz[rt[i-x]]+=sz[rt[i]];
						rt[i]=0;
					}
					max=std::min(x+tag,max);
				}
			}
			else ans[t]+=sz[rt[x+tag]];
		}
		else if(l<=r){
			for(int i=L;i<=R;i++) if(pa[i]==i) rt[a[i]]=0,a[i]-=tag;
			for(int i=L;i<=R;i++) a[i]=a[findp(i)];
//			for(int i=L;i<=R;i++) printf("%d ",a[i]);puts("");
			if(op==1){for(int i=l;i<=r;i++) if(a[i]>x) a[i]-=x;}
			else for(int i=l;i<=r;i++) if(a[i]==x) ++ans[t];
			rebuild(L,R);
		}
	}
	for(int i=L;i<=R;i++) if(pa[i]==i) rt[a[i]]=0;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("sol.out","w",stdout);
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	b=sqrt(n);
	for(int i=1;i<=m;i++) scanf("%d%d%d%d",&o[i].op,&o[i].l,&o[i].r,&o[i].x);
	for(int i=0;i*b+1<=n;i++) solve(i*b+1,std::min((i+1)*b,n));
	for(int i=1;i<=m;i++) if(o[i].op==2) printf("%d\n",ans[i]);
}
