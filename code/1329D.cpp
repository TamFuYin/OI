#include<bits/stdc++.h>
const int N=2e5+10;
char s[N],a[N];
int len[N];
std::stack<int> sta;
struct Tree{//单点修改，全局最大值
	std::priority_queue<std::pair<int,int> > q;
	int real[N];
	int operator[](const int x)const{
		return real[x];
	}
	void mdf(int x,int v){
		q.emplace(real[x]=v,x);
	}
	std::pair<int,int> max(){
		while(real[q.top().second]!=q.top().first) q.pop();
		return q.top();
	}
	void build(int a[],int n){
		while(!q.empty()) q.pop();
		for(int i=0;i<n;i++) q.emplace(real[i]=a[i],i);
	}
}t;
int cnt[N];
std::vector<std::pair<int,int> > ans;
int _m;
bool check(int x,int y){
	t.mdf(x,t[x]-1);
	t.mdf(y,t[y]-1);
	_m-=2;
	if(t.max().first*2>_m){
		_m+=2;
		t.mdf(x,t[x]+1);
		t.mdf(y,t[y]+1);
		return 0;
	}
	return 1;
}
int main(){
	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		int n=strlen(s),m=0;
		for(int i=0;i<n;i++){
			if(!i||s[i]==s[i-1]) len[m]=1,a[m++]=s[i];
			else a[m-1]=s[i],++len[m-1];
		}
		std::fill(cnt,cnt+26,0);
		std::pair<int,char> mx{0,0};
		for(int i=0;i<m-1;i++) ++cnt[a[i]-'a'];
		t.build(cnt,26);
		ans.clear();int cur=0;_m=m-1;
//		for(int i=0;i<26;i++) printf("%d ",cnt[i]);puts("");
//		printf("%d %c\n",t.max().first,'a'+t.max().second);
		for(int i=0;i<m-1;i++){
			if(!sta.empty()&&a[sta.top()]!=a[i]&&(t.max().first*2<=_m&&check(a[i]-'a',a[sta.top()]-'a')||
				a[i]=='a'+t.max().second||a[sta.top()]=='a'+t.max().second))
				ans.emplace_back(cur+1,cur+len[i]),cur-=len[sta.top()],len[i+1]+=len[sta.top()],sta.pop();
			else sta.push(i),cur+=len[i];
		}
		cur+=len[m-1];
		sta.push(m-1);
		while(!sta.empty()){
			ans.emplace_back(cur-len[sta.top()]+1,cur);
			cur-=len[sta.top()];
			sta.pop();
		}
		printf("%d\n",ans.size());
		for(auto p:ans) printf("%d %d\n",p.first,p.second);
	}
}
