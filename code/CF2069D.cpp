#include<bits/stdc++.h>
const int N=2e5+10;
std::string s;
int n;
int cnt[N];
bool check(int mid){
	for(int i=mid;n-i-1>=mid;i++) if(s[i]!=s[n-i-1]) return 0;
	for(int i=0;i<26;i++)
		if(cnt[i]/2<std::count(s.end()-std::min(n-mid,mid),s.end(),'a'+i))
			return 0;
	return 1;
}
int solve(){
	int left=0,right=n;
	while(left<right){
		int mid=left+right>>1;
		if(check(mid)) right=mid;
		else left=mid+1;
	}
	return left;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		std::cin>>s;
		while(s.front()==s.back()){
			s.erase(s.begin());
			s.erase(--s.end());
			if(s.empty()) break;
		}
		n=s.length();
		for(int i=0;i<26;i++) cnt[i]=std::count(s.begin(),s.end(),'a'+i);
		int ans=solve();
		std::reverse(s.begin(),s.end());
		printf("%d\n",std::min(ans,solve()));
	}
}