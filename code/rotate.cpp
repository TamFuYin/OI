// #include"rotate.h"
#include<bits/stdc++.h>
void rotate(std::vector<int>,int);
const int PI=5e4;
void energy(int n,std::vector<int> v){
	static std::vector<int> id(n);
	std::iota(id.begin(),id.end(),0);
	std::sort(id.begin(),id.end(),[&](int i,int j){return v[i]<v[j];});
	for(int i=0;i<n/2;i++)
		rotate({id[i+n/2]},(v[id[i]]-v[id[i+n/2]]-PI/2+PI)%PI);
}