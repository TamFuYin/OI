#include<bits/stdc++.h>
namespace flow{
	int nx[M],ls[N],to[M],ca[M],_tot=1;
	void clear(){
		memset(ls,0,sizeof ls);
		_tot=1;
	}
	void addse(int u,int v,int c){
		nx[++_tot]=ls[u];
		to[ls[u]=_tot]=v;
		ca[_tot]=c;
	}
	void add(int u,int v,int c){
		addse(u,v,c);
		addse(v,u,0);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,R,C;scanf("%d%d%d",&n,&R,&C);
		for(int i=1;i<=R;i++){
			for(int j=1;j<=C;j++){
				scanf("%d",a[i]+j);
			}
		}
	}
}