#include<bits/stdc++.h>
const int N=3e6;
char s[N];
int even,odd;
int al[N],ar[N];
void dfs(int p,int l,int r){
	if(p<=0) return;
	al[p]=l;ar[p]=r;
	if(s[l]=='T') dfs(p-2,l+1,r);
	else if(s[r]=='T') dfs(p-2,l,r-1);
	else dfs(p-2,l+1,r-1);
}
int main(){
	int n,m,ans=0;scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<=n;i++) ans+=1+(s[i]=='T');
	bool t=ans&1;
	dfs(ans,1,n);
	int l=1,r=n,tl=0,tr=0;
	while(s[l]=='T') ++tl,++l;
	while(s[r]=='T') ++tr,--r;
	if(tl<tr) dfs(ans-tl*2-1,l+1,n);
	else dfs(ans-tr*2-1,1,r-1);
	while(m--){
		int x;scanf("%d",&x);
		if(al[x]) printf("%d %d\n",al[x],ar[x]);
		else puts("NIE");
	}
}
