#include"coin.h"
#include<vector>
int Solve(int n){
	int a1=Ask({1}),a2=Ask({2});
	if(a1!=a2) return a1<a2?1:2;
	int l=1,r=n;
	while(l<r){
		int mid=l+r>>1;
		std::vector<int> vec;
		for(int i=l;i<=mid;i++) vec.push_back(i);
		int AskVec=0;
		if(l==1&&mid==2) AskVec=a1+a2;
		else if(l==1&&mid==1) AskVec=a1;
		else if(l==2&&mid==2) AskVec=a2;
		else AskVec=Ask(vec);
		if(AskVec!=a1*(mid-l+1)) r=mid;
		else l=mid+1;
	}
	return l;
}
