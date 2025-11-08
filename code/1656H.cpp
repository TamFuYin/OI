#include<bits/stdc++.h>
const int N=1e3+10;
int a[N],b[N];
struct segt{
	int t[N*4][N];
	int operator[](int x)const{
		return t[1][x];
	}
}tA,tB;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		for(int i=1;i<=m;i++)
			scanf("%d",b+i);
		int nn=n,mm=m;
		std::fill(delA+1,delA+n+1,0);
		std::fill(delB+1,delB+n+1,0);
		while(1){
			static std::queue<int> qA,qB;
			for(int i=1;i<=n;i++) if(!delA[i]&&tB[i]>1) qA.push(i),--nn;
			for(int i=1;i<=m;i++) if(!delB[i]&&tA[i]>1) qB.push(i),--mm;
			if(qA.empty()&&qB.empty()) break;
			while(!qA.empty()) tA.erase(qA.top()),qA.pop();
			while(!qB.empty()) tB.erase(qB.top()),qB.pop();
		}
		if(nn&&mm){
			printf("YES\n%d %d\n",nn,mm);
			for(int i=1;i<=n;i++) if(!delA[i]) printf("%d ",i);
			for(int i=1;i<=m;i++) if(!delB[i]) printf("%d ",i);
		}
	}
}