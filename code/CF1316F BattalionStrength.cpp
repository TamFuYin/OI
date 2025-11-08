#include<bits/stdc++.h>
const int N=1e5,MOD=1e9+7;
int sp[N],f[N],sf[N],p[N];
int qpow(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return c;
}
int n;
int lowbit(int x){return x&-x;}
struct BIT{
	int t[N];
	int query(int x){
		int ret=0;
		while(x){
			(ret+=t[x])%=MOD;
			x-=lowbit(x);
		}
		return ret;
	}
	void add(int x,int c){
		while(x<=n){
			(t[x]+=c)%=MOD;
			x+=lowbit(x);
		}
	}
	int query(int l,int r){return query(r)-query(l-1);}
}tp,tn;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",p+i);
	std::sort(p+1,p+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
		tp.add(i,1ll*p[i]*qpow(2,i)%MOD),
		tn.add(i,1ll*p[i]*qpow(2,MOD-1-i)%MOD);
	auto contr=[](int i)->int{
		return int((1ll*tp.query(i-1)*qpow(2,MOD-1-i-1)+
		1ll*tn.query(i+1,n)*qpow(2,i-1))%MOD);
	};
	for(int i=1;i<=n;i++) (ans+=1ll*p[i]*tp.query(i-1)%MOD*qpow(2,MOD-1-i-1)%MOD)%=MOD;
	printf("%d\n",ans);
	int q;scanf("%d",&q);
	while(q--){
		int i,x;scanf("%d%d",&i,&x);
		(ans+=1ll*(MOD+x-p[i])*contr(i)%MOD)%=MOD;
		tp.add(i,1ll*(MOD+x-p[i])*qpow(2,i)%MOD),
		tn.add(i,1ll*(MOD+x-p[i])*qpow(2,MOD-1-i)%MOD);
		p[i]=x;
		int tmp=0;
		for(int i=1;i<=n;i++) (tmp+=1ll*p[i]*tp.query(i-1)%MOD*qpow(2,MOD-1-i-1)%MOD)%=MOD;
	}
}