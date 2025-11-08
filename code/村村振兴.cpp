#include<bits/stdc++.h>
const int N=1e5;
struct point{double x,y;}p[N];
std::mt19937 rnd(time(0));
double sqr(double x){return x*x;}
bool cmp(double a,double b){
	return fabs(a-b)<1e-8;
}
double dis(point a,point b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
point geto(point a,point b,point c){
	double a1=2*(b.x-a.x),b1=2*(b.y-a.y),
	c1=sqr(b.x)-sqr(a.x)+sqr(b.y)-sqr(a.y),
	a2=2*(c.x-a.x),b2=2*(c.y-a.y),
	c2=sqr(c.x)-sqr(a.x)+sqr(c.y)-sqr(a.y);
	if(cmp(a1,0)) return {(c2-c1/b1*b2)/a2,c1/b1};
	else if(cmp(b1,0)) return {c1/a1,(c2-c1/a1*a2)/b2};
	else return {(c2*b1-c1*b2)/(a2*b1-a1*b2),(c2*a1-c1*a2)/(b2*a1-b1*a2)};
}
struct circle{
	point o;
	double r;
	bool in(point p){
		return dis(o,p)<r||cmp(dis(o,p),r);
	}
}c[N];
double v[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
	std::shuffle(p+1,p+n+1,rnd);
	circle o={p[1],0};
	for(int i=1;i<=n;i++){
		if(o.in(p[i])) continue;
		o={{(p[i].x+p[1].x)/2,(p[i].y+p[1].y)/2},dis(p[i],p[1])/2};
		for(int j=2;j<i;j++){
			if(o.in(p[j])) continue;
			o={{(p[i].x+p[j].x)/2,(p[i].y+p[j].y)/2},dis(p[i],p[j])/2};
			for(int k=1;k<j;k++){
				if(o.in(p[k])) continue;
				o.o=geto(p[i],p[j],p[k]);
				o.r=dis(o.o,p[i]);
			}
		}
	}
	for(int i=0;i<m;i++) scanf("%lf%lf%lf%lf",&c[i].o.x,&c[i].o.y,&c[i].r,&v[i]);
	for(int s=0;s<(1<<m);s++){
		for(int i=0;i<m;i++) if(s>>i&1) if(!c[i].in(o.o)) o.o=
	}
}