#include<bits/stdc++.h>
const int N=1e5;
int query(int p){
}
const int Nx=39989,Ny=1e9;
void update(int p,int L,int R,int l=1,int r=Nx,int o=1){
    if(L<=l&&r<=R){return;}
}
double k[N],b[N];
int main(){
    int Q;scanf("%d",&Q);
    int last_ans=0;
    for(int i=1;i<=Q;i++){
        int op;scanf("%d",&op);
        if(!op){
            int x;scanf("%d",&x);
            printf("%d",query(x));
            x=(x+last_ans-1)%Nx+1;
        }
        else{
            int x0,y0,x1,y1;
            scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
            x0=(x0+last_ans-1)%Nx+1;
            x1=(x1+last_ans-1)%Nx+1;
            y0=(y0+last_ans-1)%Ny+1;
            y1=(y1+last_ans-1)%Ny+1;
            k[i]=(double)(y1-y0)/(x1-x0);
            b[i]=y0-k[i]*x0;
            update(i,x0,x1);
        }
    }
}