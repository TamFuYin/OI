namespace LCT{
	const int N=1e5;
	struct node{int fa,son[2],sum;}t[N];
	void rotate(int p){
		int fa=t[p].fa,k=typeof(p);
		if(nroot(fa)) t[t[fa].fa].son[typeof(fa)]=p;
		t[p].fa=t[fa].fa;
		t[fa].son[k]=t[p].son[k^1];
		t[t[p].son[k^1]].fa=fa;
		t[fa].fa=p;
		t[p].son[k^1]=fa;
		pushup(fa),pushup(p);
	}
	void splay(int p){
		while(nroot(p)){
			if(nroot(fa)) rotate(typeof(p)==typeof(fa)?t[p].fa:p);
			rotate(p);
		}
	}
	void access(int p){
		for(int s=0;p;s=p,p=t[p].fa)
		splay(p),rs=s,pushup(p);
	}
}
#include<cstdio>
int main(){
}
