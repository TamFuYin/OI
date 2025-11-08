#include<bits/stdc++.h>
const int N=1e6+10,V=N*30;
int x[N];
std::set<int> bh[N*2];
int tr[V][2],mx[V],size=1,size2=0,ys[V];
void ckmax(int& a,int b){a=std::max(a,b);}
void insert(int x,int b){
	int p=1;ckmax(mx[p],b);
	for(int i=29;i>=0;i--){
		int &q=tr[p][x>>i&1];
		if(!q) q=++size;
		p=q;
		ckmax(mx[p],b);
	}
	if(!ys[p]) ys[p]=++size2;
	bh[ys[p]].insert(b);
}
void erase(int x,int b){
	static int sta[40];
	int top=0,p=1;
	for(int i=29;i>=0;i--){
		sta[++top]=p;
		int &q=tr[p][x>>i&1];
		if(!q) q=++size;
		p=q;
	}
	bh[ys[p]].erase(b);
	if(bh[ys[p]].empty()) mx[p]=0;
	else mx[p]=*bh[ys[p]].rbegin();
	for(int i=top;i>=1;i--)
		mx[sta[i]]=std::max(mx[tr[sta[i]][0]],mx[tr[sta[i]][1]]);
}
int n;
int solve(int a,int b){
	int s1=0,s2=0,p=1,tmp;
	for(int i=29;i>=0;i--){
		if(b>>i&1) ckmax(s1,mx[tr[p][a>>i&1]]),p=tr[p][a>>i&1^1];
		else ckmax(s2,mx[tr[p][a>>i&1^1]]),p=tr[p][a>>i&1];
	}
	if(!bh[ys[p]].empty()){
		tmp=*bh[ys[p]].begin();
		if(tmp==n) --tmp;
		return tmp;
	}
	int ret=s1==n?s2:s1;
	if(ret==0) ret=-1;
	return ret;
}
int main(){
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
	int q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",x+i);
		insert(x[i],i);
	}
	while(q--){
		int opt,k,v;scanf("%d%d%d",&opt,&k,&v);
		if(opt==1) erase(x[k],k),insert(x[k]=v,k);
		else printf("%d\n",solve(k,v));
	}
}
