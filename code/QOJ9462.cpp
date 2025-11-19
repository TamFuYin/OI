#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
struct point{
    double x,y;
    point(double x=0,double y=0):x(x),y(y){}
};
struct circle{
    point p;
    double r;
    circle(point p,double r):p(p),r(r){}double operator&(circle c){ // 两圆交面积
        double d = hypot(p.x - c.p.x, p.y - c.p.y);
        double r1 = r, r2 = c.r;
        if(d >= r1 + r2) return 0.0;              // 相离
        if(d <= fabs(r1 - r2)) {                 // 包含
            double R = std::min(r1, r2);
            return M_PI * R * R;
        }
        double alpha = acos((r1*r1 + d*d - r2*r2) / (2*r1*d)) * 2;
        double beta  = acos((r2*r2 + d*d - r1*r1) / (2*r2*d)) * 2;
        double area1 = 0.5 * r1*r1 * (alpha - sin(alpha));
        double area2 = 0.5 * r2*r2 * (beta - sin(beta));
        return area1 + area2;
    }
};
const int N=1e5;
std::pair<double,int> a[N];
const double eps=1e-8;
bool eq(double a,double b){return std::fabs(a-b)<eps;}
int b[N];
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int n,R,r;scanf("%d%d%d",&n,&R,&r);
        for(int i=1;i<=n;i++){
            int x,y;scanf("%d%d",&x,&y);
            a[i]={circle(point(x,y),r)&circle(point(0,0),R-r),i};
        }
        std::sort(a+1,a+n+1);std::reverse(a+1,a+n+1);
        int m=0;
        while(eq(a[m+1].first,a[1].first)) ++m;
        for(int i=1;i<=m;i++) b[i]=a[i].second;
        std::sort(b+1,b+m+1);
        printf("%d\n",m);
        for(int i=1;i<=m;i++) printf("%d ",b[i]);
        puts("");
    }
}