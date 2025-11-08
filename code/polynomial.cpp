#include<bits/stdc++.h>
namespace polynomial{
	const int MOD=998244353;
	std::map<int,int> pr3;
	int qpow(int a,int b){
		int ret=1;
		if(a==3&&pr3.find(b)!=pr3.end()) return pr3[b];
		while(b){
			if(b&1) ret=1ll*ret*a%MOD;
			a=1ll*a*a%MOD;b>>=1;
		}
		if(a==3) pr3[b]=ret;
		return ret;
	}
	using poly=std::vector<int>;
	poly berlekamp_massey(poly a){
		poly ans,lst;
		int k,invdeltak,lv=-1;
		for(int i=0;i<a.size();i++){
			int delta=a[i];
			for(int j=0;j<ans.size();j++)
				delta=(delta+MOD-1ll*a[i-1-j]*ans[j]%MOD)%MOD;
			if(delta==0) continue;
			std::vector<int> tmp=ans;
			if(ans.size()==0) for(int j=0;j<=i;j++) ans.push_back(0);
			else{
				int tmp=1ll*delta*invdeltak%MOD;
				if(ans.size()<i-k+lst.size()) ans.resize(i-k+lst.size());
				(ans[i-k-1]+=tmp)%=MOD;
				for(int j=0;j<lst.size();j++)
					(ans[i-k+j]+=1ll*(MOD-tmp)*lst[j]%MOD)%=MOD;
			}
			if(i-int(tmp.size())>lv) lv=i-tmp.size(),lst=tmp,invdeltak=qpow(delta,MOD-2),k=i;
		}
		return ans;
	}
	std::vector<int> swap;
	using ll=long long;
	poly fft(poly a,bool opt=1){
		if(a.size()>swap.size()) swap.resize(a.size());
		for(int i=0;i<a.size();i++) swap[i]=swap[i>>1]>>1|(i&1?a.size()>>1:0);
		for(int i=0;i<a.size();i++) if(swap[i]<i) std::swap(a[i],a[swap[i]]);
		for(int n=2;n<=a.size();n*=2){
			for(int i=0,wn=qpow(3,(MOD-1)/n*(opt?1:n-1));i<a.size();i+=n){
				for(register int j=i,w=1,t;j<i+n/2;j++){
					t=(ll)a[j+n/2]*w%MOD;
					a[j+n/2]=(a[j]+MOD-t)%MOD;
					a[j]=(a[j]+t)%MOD;
					w=(ll)w*wn%MOD;
				}
			}
		}
		if(!opt){
			int tmp=qpow(a.size(),MOD-2);
			for(int i=0;i<a.size();i++) a[i]=1ll*a[i]*tmp%MOD;
		}
		return a;
	}
#define ifft(a) fft(a,0)
	poly resize(poly a,int n){
		a.resize(n);return a;
	}
	poly operator*(poly a,poly b){
		int fact_n=a.size()+b.size()-1,n=1<<int(ceil(log2(fact_n)));
		poly ans(n);a=fft(resize(a,n));b=fft(resize(b,n));
		for(int i=0;i<n;i++) ans[i]=(ll)a[i]*b[i]%MOD;
		return resize(ifft(ans),fact_n);
	}
	poly operator-(poly a){
		for(int i=0;i<a.size();i++) a[i]=MOD-a[i];
		return a;
	}
	poly operator+(poly a,int b){
		(a[0]+=b)%=MOD;return a;
	}
	poly operator+(poly a,poly b){
		poly ans(std::max(a.size(),b.size()));
		for(int i=0;i<a.size()&&i<b.size();i++) ans[i]=(a[i]+b[i])%MOD;
		for(int i=b.size();i<a.size();i++) ans[i]=a[i];
		for(int i=a.size();i<b.size();i++) ans[i]=b[i];
		return ans;
	}
	poly operator-(poly a,poly b){return a+(-b);}
	poly operator-(poly a,int b){return a+(-b);}
	poly operator+(int a,poly b){return b+a;}
	poly operator-(int a,poly b){return (-b)+a;}
	poly inv(poly f){
		int fact_n=f.size();f.resize(1<<int(ceil(log2(fact_n))));
		poly ans(1);ans[0]=qpow(f[0],MOD-2);
		for(int n=2;n<=f.size();n*=2)
			ans=resize(ans*(-resize(resize(f,n)*ans,n)+2),n);
		return resize(ans,fact_n);
	}
	poly rev(poly a){
		for(int i=0;i<a.size()/2;i++) std::swap(a[i],a[a.size()-i-1]);
		return a;
	}
	poly operator/(poly f,poly g){
		int n=f.size(),m=g.size();
		return rev(resize(resize(rev(f),n-m+1)*inv(resize(rev(g),n-m+1)),n-m+1));
	}
	poly operator%(poly f,poly g){
		if(f.size()<g.size()) return f;
		return resize(f-f/g*g,g.size()-1);
	}
	int recurrence(poly f,poly a,int n){
		f=-rev(f);f.push_back(1);
		poly g(2),b(1);
		g[1]=1;b[0]=1;
		while(n){
			if(n&1) b=b*g%f;
			g=g*g%f;n>>=1;
		}
		int ret=0;
		for(int i=0;i<b.size();i++)
			ret=(ret+1ll*a[i]*b[i]%MOD)%MOD;
		return ret;
	}
	poly D(poly a){
		for(int i=0;i<a.size()-1;i++) a[i]=1ll*a[i+1]*(i+1)%MOD;
		a.pop_back();return a;
	}
	poly S(poly a){
		a.push_back(0);
		for(int i=a.size()-1;i>=1;i--) a[i]=1ll*a[i-1]*qpow(i,MOD-2)%MOD;
		a[0]=0;return a;
	}
	poly ln(poly a){
//		poly tmp=a;
//		for(int i=0;i<tmp.size();i++) printf("%d ",tmp[i]);puts("");
		return resize(S(D(a)*inv(a)),a.size());
	}
	poly exp(poly f){
		int fact_n=f.size();
		f.resize(1<<int(ceil(log2(fact_n))));
		poly ans(1);ans[0]=1;
		for(int m=2;m<=f.size();m*=2){
			ans=resize(ans*(-ln(resize(ans,m))+resize(f,m)+1),m);
//			for(int i=0;i<m;i++) printf("%d ",ans[i]);puts("");
		}
		return ans;
	}
	poly euler(poly a){
		poly ans(a.size());
		for(int n=1;n<a.size();n++){
			int tmp=qpow(n,MOD-2);
			for(int i=0;n*i<a.size();i++){
				(ans[n*i]+=1ll*a[i]*tmp%MOD)%=MOD;
			}
		}
		return exp(ans);
	}
}
using namespace polynomial;
int main(){
	int n;scanf("%d",&n);poly g(n);
	for(int i=1;i<n;i++) scanf("%d",&g[i]);
	poly f=inv(1-g);
	for(int i=0;i<n;i++) printf("%d ",f[i]);
}
