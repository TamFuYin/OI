#include"poly.h"
const int N=1e6;
int a[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	poly(a,1<<int(ceil(log2(n)))).inv();
	for(int i=0;i<n;i++) printf("%d ",a[i]);
}
