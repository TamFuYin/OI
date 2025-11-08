#include<bits/stdc++.h>
#define Assert(A) ({if(!(A)) fprintf(stderr,"Error "#A),exit(1);})
const int MOD=998244353;
using ll=long long;
int qpow(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=(ll)c*a%MOD;
		a=(ll)a*a%MOD;b>>=1;
	}
	return c;
}
const int N=20;
struct comp0{
	int a,k;
	comp0(int a=0,int k=0):a(a),k(k){}
	comp0 operator+(const comp0& b)const{
		if(k==b.k) return {(a+b.a)%MOD,k};
		else return k<b.k?*this:b;
	}
	comp0 operator*(const comp0& b)const{
		return comp0(1ll*a*b.a%MOD,k+b.k);
	}
	comp0 operator+=(const comp0& b){return *this=*this+b;}
	comp0 operator*=(const comp0& b){return *this=*this*b;}
	comp0 operator-()const{return {MOD-a,k};}
	int operator/(const comp0& b)const{
		Assert(b.k<=k);
		return b.k==k?(ll)a*qpow(b.a,MOD-2)%MOD:0;
	}
}f[1<<N],F[1<<N];
int g[1<<N];
int a[1<<N];
template<typename T,typename Op>
void supset(T f[],int n,Op op){
	for(int i=0;i<n;i++)
		for(int s=0;s<(1<<n);s++)
			if(s>>i&1) op(f[s^1<<i],f[s]);
}
template<typename T,typename Op>
void subset(T f[],int n,Op op){
	for(int i=0;i<n;i++)
		for(int s=0;s<(1<<n);s++)
			if(s>>i&1) op(f[s],f[s^1<<i]);
}
int outp(int x){
	if(x>MOD/2) return x-MOD;
	return x;
}
comp0 tmp[1<<N];
#define popc __builtin_popcount
int main(){
	int c,t;scanf("%d%d",&c,&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int s=0;s<(1<<n);s++){
			scanf("%d",a+s);
			if(a[s]==MOD-1) f[s]={1,1};
			else f[s]=1+a[s];
			g[s]=(1+2*a[s])%MOD;
		}
		supset(g,n,[](int& a,const int& b){a=1ll*a*b%MOD;}),
		supset(f,n,[](comp0& a,const comp0& b){a*=b;});
		std::copy(f,f+(1<<n),F);
		for(int s=0;s<(1<<n);s++)
			F[s]*=(1ll<<popc(s))*(popc(s)&1?MOD-1:1)%MOD;
		subset(F,n,[](comp0& a,const comp0& b){a+=b;});
		for(int s=0;s<(1<<n);s++) F[s]*=F[s];
		subset(F,n,[](comp0& a,const comp0& b){a+=-b;});
		int ans=0;
		for(int s=0;s<(1<<n);s++)
			(ans+=1ll*(F[s]/(f[s]*f[s]))*g[s]%MOD*qpow((MOD+1)/2,popc(s))%MOD)%=MOD;
		printf("%d\n",ans);
	}
}
