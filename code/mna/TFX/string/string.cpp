#include<bits/stdc++.h>
std::vector<int> a;
std::string s,t,p,ans;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	std::cin>>s>>t;
	int n=s.length(),cur=-1;
	for(char c='z';c>='a';c--){
		std::vector<int> v;
		for(int i=cur+1;i<n;i++)
			if(s[i]==c) v.push_back(i),cur=i;
		std::sort(v.begin(),v.end(),[](int x,int y){return t[x]>t[y]||t[x]==t[y]&&x>y;});
		a.insert(a.end(),v.begin(),v.end());
	}
	for(auto i=a.begin();i!=a.end();i++){
		std::sort(a.begin(),i+1);p.clear();
		for(auto j=a.begin();j!=i+1;j++) p.push_back(s[*j]);
		for(auto j=a.begin();j!=i+1;j++) p.push_back(t[*j]);
		if(p>ans) ans=p;
	}
	std::cout<<ans;
}
