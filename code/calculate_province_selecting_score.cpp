#include<bits/stdc++.h>
double fix(double x,int a){
    return floor(x*a+(int(x*a*10)%10>=5))/a;
}
int main(){
    int noip,gdoi;
    printf("input your NOIP point,please: ");
    scanf("%d",&noip);
    printf("input your GDOI point,please: ");
    scanf("%d",&gdoi);
    const double lhf_noip=400,lhf_gdoi=476;
    printf("Hence, your total point is %.4lf\n",fix(noip/lhf_noip*100*0.3,1e4)+fix(gdoi/lhf_gdoi*100*0.7,1e4));
    system("pause");
}