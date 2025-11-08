#include<bits/stdc++.h>
const int N=1e5;
int ans[N]={1,1,2,4,9,20,46,105,243,561,1301,3014,6995,16227,37668,87426,202960,471146,1093803,2539294,5895236,13686295,31774289,73767403,171259671,397598948};
int main(){
	freopen("split.in","r",stdin);
	freopen("split.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]%m);
}
