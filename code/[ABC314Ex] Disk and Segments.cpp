#include<bits/stdc++.h>
#define th (*this)
struct vector{
	double x,y;
	double operator^(const vector& b)const{
		return x*b.y-y*b.x;//叉积
	}
	double operator&(const vector& b)const{
		return x*b.x+y*b.y;//点积
	}
	double operator&()const{
		return th&th;//范数的平方
	}
	double length()const{
		return sqrt(&th);
	}
	vector operator*(double a)const{
		return {x*a,y*a};
	}
};
struct point{
	double x,y;
	point operator+(const vector& v)const{
		return {x+v.x,y+v.y};
	}
	point& operator+=(const vector& v){
		return th=th+v;
	}
	vector operator-(const point& p)const{
		return {x-p.x,y-p.y};
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
};
struct line{
	point s;
	vector v;
	point nest(point p){
		double t=((p-s)&v)/(v&v);
		if(0<=t&&t<=1) return s+v*t;
		if(&(p-s)<&(p-(s+v))) return s;
		else return s+v;
	}
	double dist(point p){
		return (p-nest(p)).length();
	}
};
const int N=1e5,M=1e3+1;
line a[N];
std::mt19937 rnd(time(0));
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		point s,e;s.read();e.read();
		a[i].s=s,a[i].v=e-s;
	}
	double ans=INFINITY;
	int times=5;//多次模拟退火
	while(times--){
		double T=100;
		point w{double(rnd()%M),double(rnd()%M)};
		while(T>=1e-8){
			double dis=0;point p=w;
			for(int i=1;i<=n;i++)
				if(a[i].dist(w)>dis)
					dis=a[i].dist(w),
					p=a[i].nest(w);
			w+=(p-w)*(T/dis);
			ans=std::min(ans,dis);
			T*=0.98;
		}
	}
	printf("%.10lf",ans);
}