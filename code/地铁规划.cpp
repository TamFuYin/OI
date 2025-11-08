#include"subway.h"
#include<bits/stdc++.h>
int m;
void init(int _n,int _m,int _lim){
	m=_m;
	return;
}
const int N=1e7;
std::bitset<N> state;
std::stack<int> sta,tmpB,tmpA;
std::queue<int> tmpQ;
int r=0,cnt=0;
int lowbit(int x){
	return x&-x;
}
int solve(int l){
	if(l!=1){
		if(!cnt){
			cnt=sta.size()-1;
			while(!sta.empty()) tmpQ.push(sta.top()),undo(),sta.pop();
			while(tmpQ.size()>1) merge(tmpQ.front()),sta.push(tmpQ.front()),state[tmpQ.front()]=0,tmpQ.pop();
			tmpQ.pop();
		}
		else{
			assert(cnt);
			int k=lowbit(cnt);
			while(k--){
				while(state[sta.top()]) tmpB.push(sta.top()),undo(),sta.pop();
				tmpA.push(sta.top()),undo(),sta.pop();
			}
			while(!tmpB.empty()) merge(tmpB.top()),sta.push(tmpB.top()),tmpB.pop();
			while(tmpA.size()>1){
				merge(tmpA.top());
				sta.push(tmpA.top());
				tmpA.pop();
			}
			tmpA.pop();cnt--;
		}
	}
	while(r<m&&check(r+1)) merge(++r),state[r]=1,sta.push(r);
	return r;
}
