#include<bits/stdc++.h>
const int N=210;
struct data{
    int v,x,y;
    data(int v=-100,int x=0,int y=0):v(v),x(x),y(y){}
    bool operator<(const data& b)const{
        return v<b.v;
    }
    bool check(int tot)const{
        return v<3&&tot-v<3;
    }
}f[6][N][N];
template<typename T>
void ckmax(T& a,T b){
    a=std::max(a,b);
}
const int a[]={0,25,25,25,25,15};
std::pair<int,int> outp[6];
int main(){
    // freopen64(".in","r",stdin);
    f[0][0][0]={0,0,0};
    for(int i=1;i<=5;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                if(j>=a[i]) for(int l=0;l<=k&&l<=a[i]-2;l++) if(f[i-1][j-a[i]][k-l].check(i-1))
                    ckmax(f[i][j][k],{f[i-1][j-a[i]][k-l].v+1,a[i],l});
                if(k>=a[i]) for(int l=0;l<=j&&l<=a[i]-2;l++) if(f[i-1][j-l][k-a[i]].check(i-1))
                    ckmax(f[i][j][k],{f[i-1][j-l][k-a[i]].v,l,a[i]});
                for(int l=25;l<=j&&l-2<=k;l++) if(f[i-1][j-l][k-(l-2)].check(i-1))
                    ckmax(f[i][j][k],{f[i-1][j-l][k-(l-2)].v+1,l,l-2});
                for(int l=25;l<=k&&l-2<=j;l++) if(f[i-1][j-(l-2)][k-l].check(i-1))
                    ckmax(f[i][j][k],{f[i-1][j-(l-2)][k-l].v,l-2,l});
            }
        }
    }
    int T;scanf("%d",&T);
    while(T--){
        int a,b;scanf("%d%d",&a,&b);
        std::pair<int,int> ans={-10,-1};
        for(int i=1;i<=5;i++)
            if(f[i][a][b].v==3||i-f[i][a][b].v==3) ckmax(ans,std::make_pair(2*f[i][a][b].v-i,i));
        if(ans.second==-1){
            puts("Impossible");
            continue;
        }
        printf("%d:%d\n",(ans.first+ans.second)/2,(ans.second-ans.first)/2);
        for(int i=ans.second;i>=1;i--){
            data tmp=f[i][a][b];
            outp[i]={tmp.x,tmp.y},
            a-=tmp.x,b-=tmp.y;
        }
        for(int i=1;i<=ans.second;i++) printf("%d:%d ",outp[i].first,outp[i].second);
        puts("");
    }
}