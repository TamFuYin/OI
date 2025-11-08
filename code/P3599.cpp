#include<bits/stdc++.h>
int main(){
	int n,s=0;scanf("%d",&n);
	for(int i=1;i<n;i++){
		if(i&1) s+=i;
		else s-=i;
	}
}
