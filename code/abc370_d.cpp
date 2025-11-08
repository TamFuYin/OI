#include<bits/stdc++.h>
const int N=4e5+10;
std::set<std::pair<int,int> >none;
std::set<std::pair<int,int> >sr[N],sc[N];
using spii=std::set<std::pair<int,int> >;
using spit=spii::iterator;
#define mp(a,b) std::make_pair(a,b)
#define l first
#define r second
void add_point(spii& s,int k){
	spit cur=s.insert(mp(k,k)).first;
	if(cur!=s.begin()){
		spit last=std::prev(cur);
		if(last->r+1==k){
			int l=last->l;
			s.erase(last),s.erase(cur);
			cur=s.insert(mp(l,k)).first;
		}
	}
	if(std::next(cur)!=s.end()){
		spit next=std::next(cur);
		if(next->l-1==k){
			int l=cur->l,r=next->r;
			s.erase(cur),s.erase(next);
			s.insert(mp(l,r));
		}
	}
}
std::pair<int,int> add_interval(spii& s,int k){
	spit cur=--s.upper_bound(mp(k,k));
	int l=cur->l-1,r=cur->r+1;
	auto ret=mp(l,r);
	s.erase(cur),cur=s.insert(mp(l,r)).first;
	if(cur!=s.begin()){
		spit last=std::prev(cur);
		if(last->r+1==l){
			l=last->l;
			s.erase(last),s.erase(cur);
			cur=s.insert(mp(l,r)).first;
		}
	}
	if(std::next(cur)!=s.end()){
		spit next=std::next(cur);
		if(next->l-1==r){
			r=next->r;
			s.erase(cur),s.erase(next);
			s.insert(mp(l,r));
		}
	}
	return ret;
}
int main(){
	int h,w,q;scanf("%d%d%d",&h,&w,&q);
	while(q--){
		int r,c;scanf("%d%d",&r,&c);
		if(none.find(mp(r,c))==none.end()){
			none.insert(mp(r,c));
			add_point(sr[r],c);
			add_point(sc[c],r);
			continue;
		}
		auto ac=add_interval(sr[r],c);
		if(ac.first>=1) none.insert(mp(r,ac.first)),add_point(sc[ac.first],r);
		if(ac.second<=w) none.insert(mp(r,ac.second)),add_point(sc[ac.second],r);
		auto ar=add_interval(sc[c],r);
		if(ar.first>=1) none.insert(mp(ar.first,c)),add_point(sr[ar.first],c);
		if(ar.second<=h) none.insert(mp(ar.second,c)),add_point(sr[ar.second],c);
	}
	printf("%lld",1ll*h*w-none.size());
}
