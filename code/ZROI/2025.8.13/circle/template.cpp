#include<bits/stdc++.h>
using namespace std;
#define ld long double
const ld pi=acos(-1);
int n,q,i,j;
struct node{//Point
	ld x,y;
	ld abs(){return sqrt(x*x+y*y);}
	ld norm(){return x*x+y*y;}
	ld arg(){return atan2(y,x);}
	void outp(){printf("%Lf %Lf\n",x,y);}
};
node operator +(node a,node b){return node{a.x+b.x,a.y+b.y};}
node operator -(node a,node b){return node{a.x-b.x,a.y-b.y};}
node operator *(node a,ld b){return node{a.x*b,a.y*b};}
node operator /(node a,ld b){return node{a.x/b,a.y/b};}
ld operator ^(node a,node b){return a.x*b.y-a.y*b.x;}
ld operator *(node a,node b){return a.x*b.x+a.y*b.y;}
node rot(node a,ld th){return node{a.x*cos(th)-a.y*sin(th),a.y*cos(th)+a.x*sin(th)};}
struct cir{//Circle
	node c;ld r;
};
struct edg{//Line
	node st,ed;
	edg(){}
	edg(node a,node b){st=a,ed=b;}
};
inline ld Cpr(node a,node b,node c){return b-a^c-a;}
inline node LLCr(edg a,edg b){//line-line cross point
	ld S1=Cpr(a.st,b.ed,a.ed),S2=Cpr(a.st,b.st,a.ed);
	return node{(b.st.x*S1-b.ed.x*S2)/(S1-S2),(b.st.y*S1-b.ed.y*S2)/(S1-S2)};
}
vector<node> CCCr(cir A,cir B){//circle-circle cross point
	node u=B.c-A.c;
	ld a=A.r,b=B.r,c=u.abs();
	if(a+b<=c) return {};
	if(fabs(a-b)>=c) return {};
	ld w=acos((a*a+c*c-b*b)/2/a/c);
	u=u/c*a;
	return {A.c+rot(u,-w),A.c+rot(u,w)};
}
vector<node> CLCr(cir A,edg B){//circle-line cross point
	node a=B.st-A.c,b=B.ed-A.c;
	ld r=A.r;
	ld di=fabs((a^b-a)/(b-a).abs());
	if(di>=r) return {};
	ld x=a*(b-a),y=(b-a).norm(),d=x*x-y*(a.norm()-r*r);
	if(d<0) d=0;
	node m=a-(b-a)*(x/y),dr=(b-a)*(sqrt(d)/y);
	return {A.c+m-dr,A.c+m+dr};
}
int main()
{
	node A={1,1},B={5,3},C={2,4},D={5,-2},F={0,-3};
	printf("B-A: ");(B-A).outp();
	edg l1(A,B),l2(C,D);
	node E=LLCr(l1,l2);
	printf("E: ");E.outp();
	cir CF={F,5},CE={E,sqrt(5)};
	vector<node> ret1=CLCr(CF,l2);
	printf("F&CD:\n");
	for(auto j:ret1) j.outp();
	vector<node> ret2=CCCr(CF,CE);
	printf("E&F:\n");
	for(auto j:ret2) j.outp();
	return 0;
}
