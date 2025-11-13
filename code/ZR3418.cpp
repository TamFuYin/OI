#pragma GCC optimize(3)
#include<bits/stdc++.h>
using ll=long long;
template<typename T>void ckmin(T&a,T b){a=a<b?a:b;}
const int N=1e7+10;
ll f[N];
std::string A,B;
int pA[N],pB[N],qA[N],qB[N],cA,cB;
const ll INF=1e17;
int _las[2*N],*las=_las+N;
int main(){
    // freopen("ex_mujica4.in","r",stdin);
    // freopen("ex_mujica4.out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int T;std::cin>>T;
    while(T--){
        int n,X,Y;std::cin>>n>>X>>Y>>A>>B;
        cA=cB=0;f[0]=0;ll m1=0,sx=0;
        memset(las-n,-1,sizeof(int)*2*(n+1));
        las[0]=0;
        for(int i=1;i<=n;i++){
            if(A[i-1]=='1') pA[qA[i]=++cA]=i;
            else qA[i]=qA[i-1];
            if(B[i-1]=='1') pB[qB[i]=++cB]=i;
            else qB[i]=qB[i-1];
            sx+=(A[i-1]!=B[i-1])*Y;
            f[i]=sx+m1;
            int t=qA[i]-qB[i];
            if(~las[t]){
                ll w=0;
                auto abs=[](int x,int y){return x>y?x-y:y-x;};
                for(int j=qA[las[t]]+1;j<=qA[i];j++)
                    w+=abs(pA[j],pB[j-t]);
                ckmin(f[i],f[las[t]]+w*X);
            }
            ckmin(m1,f[i]-sx);
            las[t]=i;
        }
        std::cout<<f[n]<<'\n';
    }
}