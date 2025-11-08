#include<bits/stdc++.h>
const int N=2e5+10,T=N*2;
int t[T];
int lowbit(int x){
	return x&-x;
}
void add(int x,int c){
	while(x<T){
		t[x]+=c;
		x+=lowbit(x);
	}
}
int ask(int x){
	int ret=0;
	while(x){
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
int fa[N],siz[N],son[N][2],col[N],ctot;
bool isrt(int x){
	return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
}
bool typ(int x){
	return son[fa[x]][1]==x;
}
bool rev[N];
void pushup(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}
void push(int x){
	rev[x]^=1;
	std::swap(son[x][0],son[x][1]);
}
void pushdown(int x){
	if(rev[x]){
		if(son[x][0]) push(son[x][0]);
		if(son[x][1]) push(son[x][1]);
		rev[x]=0;
	}
}
int update(int x){
	static int rt;
	if(!isrt(x)) rt=update(fa[x]);
	else rt=x;
	pushdown(x);
	return rt;
}
void rotate(int x){
	int p=fa[x];bool t=typ(x);
	if(!isrt(p)) son[fa[p]][typ(p)]=x;
	fa[x]=fa[p];
	fa[son[p][t]=son[x][t^1]]=p;
	fa[son[x][t^1]=p]=x;
	pushup(p),pushup(x);
}
void splay(int x){
	static int rt;
	col[x]=col[rt=update(x)];
	if(rt!=x) col[rt]=0;
	while(!isrt(x)){
		if(!isrt(fa[x])) rotate(typ(x)==typ(fa[x])?fa[x]:x);
		rotate(x);
	}
}
void access(int x,bool tag=0){
	int p;
	for(p=0;x;p=x,x=fa[x]){
		splay(x);
		if(col[x]){
			add(col[x],-siz[x]+siz[son[x][1]]);
			col[son[x][1]]=col[x],col[x]=0;
		}
		son[x][1]=p;
		pushup(x);
	}
	if(tag) add(col[p]=++ctot,siz[p]);
}
void makeroot(int x,bool tag=0){
	access(x,tag);
	splay(x);
	push(x);
}
void link(int u,int v){
	makeroot(u);
	splay(u);
	fa[u]=v;
}
int when(int x){
	splay(x);
	return ask(col[x]-1)+siz[son[x][1]]+1;
}
int main(){
	int n,q;scanf("%d%d",&n,&q);
	std::fill(siz+1,siz+n+1,1);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),link(u,v);
	makeroot(n);
	for(int i=1;i<n;i++) access(i,1);
	while(q--){
		static char s[10];
		int u,v;
		scanf("%s%d",s,&u);
		switch(s[0]){
			case 'u':makeroot(u,1);break;
			case 'w':printf("%d\n",when(u));break;
			case 'c':scanf("%d",&v);printf("%d\n",when(u)<when(v)?u:v);break;
		}
	}
}
