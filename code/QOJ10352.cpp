#include<bits/stdc++.h>
const int N=5e4+10,MOD=1e9+7;
using bitset=std::bitset<N>;
bool bany[N];
bitset b[N],a;
std::string s;
int len,rnk;
bool add(bitset a){
	if(rnk==len) return 0;//剪枝
	for(int i=0;i<len;i++){
		if(a[i]){
			if(bany[i]) a^=b[i];
			else{
				b[i]=a,bany[i]=1;
//				printf(">>> %d\n",i);
				return 1;
			}
		}
	}
	return 0;
}
int pow2[N];
int main(){
	pow2[0]=1;for(int i=1;i<N;i++) pow2[i]=pow2[i-1]*2%MOD;
	std::cin>>s;
	int n=s.length(),ans=0;
	for(int i=0;i<n;i++) a[i]=s[i]=='1';
	for(len=n,rnk=0;len>=1;len--){
		if(bany[len]) --rnk;
		rnk+=add(a);
//		printf("dim=%d rnk=%d\n",len,rnk);
//		std::cout<<a.to_string().substr(N-20,N-1)<<'\n';
		(ans+=pow2[len-rnk])%=MOD;
		a>>=1;
	}
	printf("%d",ans);
}
