#include<bits/stdc++.h>
int main(){
	for(int n=2;n<=10000;n++){
		int s=0;
		for(int i=1;i<n;i++) s+=i^n-i;
		printf("%d ",s);
	}
}
