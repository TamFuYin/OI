#include<bits/stdc++.h>
const int N=2e5+10;
char s[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,x,y;scanf("%d%d%d%s",&n,&x,&y,s);
        int h=0,w=0;
        for(int i=0;i<n;i++){
            if(s[i]=='8'){
                ++h,++w;
            }
            else{
                ++h;
            }
        }
        if(x<0) x=-x;
        if(y<0) y=-y;
        if(x>y) std::swap(x,y);
        puts(y+std::max(x-w,0)<=h?"YES":"NO");
    }
}