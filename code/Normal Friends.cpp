/*神秘拓展 LCT*/
#include<bits/stdc++.h>
const int N=1e5;
struct splayTree{
	int ls[N],rs[N];
	void splay(int x){}
};
int lt[N],rt[N];
int lf[N];
bool tag[N];
int cnt;
int build(int l,int r){
	if(l==r) return ++cnt;
	int mid;scanf("%d",&mid);
	++cnt;
	lc[cnt]=build(l,mid),
	rc[cnt]=build(mid+1,r);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	build(1,n);
}
