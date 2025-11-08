#include<bits/stdc++.h>
const int N=3e5;
int a[N];int n;
std::map<int,int> b;
std::vector<std::map<int,int>::iterator> tmp;
bool check(int c){
	b.clear();
	for(int i=1;i<=n;i++){
		if(a[i]<=a[i-1]){
			tmp.clear();
			for(auto p=b.upper_bound(a[i]);p!=b.end();p++) tmp.push_back(p);
			for(auto p:tmp) b.erase(p);
			for(int m=a[i];;m--){
				if(!m) return 0;
				if(b.find(m)==b.end()){
					if(c==1) return 0;
					b[m]=1;
					break;
				}
				else{
					if(b[m]==c-1) b.erase(m);
					else {++b[m];break;}
				}
			}
		}
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int left=1,right=n;
	while(left<right){
		int mid=left+right>>1;
		if(check(mid)) right=mid;
		else left=mid+1;
	}
	printf("%d",left);
}
