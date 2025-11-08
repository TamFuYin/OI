#include<bits/stdc++.h>
const int N=1e5;
struct point{double x,y;}a[N];
struct vector{
    double x,y;
    vector(const double& a,const double& b):x(a),y(b){}
    vector operator*(const double& a)const{return {x*a,y*a};}
    vector operator/(const double& a)const{return {x/a,y/a};}
    double square()const{return x*x+y*y;}
};
point operator+(const point& a,const vector& b){return {a.x+b.x,a.y+b.y};}
double operator&(const vector& a,const vector& b){return a.x*b.x+a.y*b.y;}
double operator*(const vector& a,const vector& b){return a.x*b.y-a.y*b.x;}
vector operator-(const point& a,const point& b){return {a.x-b.x,a.y-b.y};}
struct matrix{
    vector a,b;
    matrix(const vector& a,const vector& b):a(a),b(b){}
    matrix inverse()const{
        double delta=a*b;
        return matrix(vector(b.y,-a.y)/delta,vector(-b.x,a.y)/delta);
    }
};
vector operator*(const matrix& a,const vector& b){return {a.a&b,a.b&b};}
struct circle{
    point O;double r;
    circle(const point& O,const double& r):O(O),r(r){}
    circle(const point& p1,const point& p2,const point& p3){
        O=p1+matrix(p2-p1,p3-p1).inverse()*vector((p2-p1).square()/2,(p3-p1).square()/2);
        r=sqrt((p1-O).square());
    }
    bool inside(const point& p)const{
        return (p-O).square()<=r*r;
    }
};
int n;
circle mcc()
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
}