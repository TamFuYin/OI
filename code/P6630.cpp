#include<bits/stdc++.h>
const int N=1e5;
int m[N],dfn;
void dfs(int l,int r){
	if(l==r){
		return;
	}
	int mid=m[++dfn];
	dfs(l,mid);
	dfs(mid+1,r);
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++) scanf("%d",m+i);
	dfs(1,n);
}
