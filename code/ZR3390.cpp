#include<bits/stdc++.h>
template<typename T>void ckmin(T &a,T b){if(b<a)a=b;}
const int N=5e2+10;
int f[N][N][N];
int a[N],s[N];
int main(){
    // freopen64("ex_code5.in","r",stdin);
    // freopen64("ex_code2.out","w",stdout);
    int n,A,B;scanf("%d%d%d",&n,&A,&B);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    if(A==B){
        std::priority_queue<int,std::vector<int>,std::greater<int>> q;
        for(int i=1;i<=n;i++) q.push(a[i]);
        int ans=0;
        while(q.size()>1){
            int x=q.top();q.pop();
            int y=q.top();q.pop();
            ans+=x+y;
            q.push(x+y);
        }
        printf("%d\n",ans*A);
        return 0;
    }
    std::sort(a+1,a+n+1,std::greater<int>());
    for(int i=n;i>=1;i--) s[i]=s[i+1]+a[i];
    memset(f,0x3f,sizeof f);
    f[1][0][0]=0;
    for(int l=0;l<=n;l++){
        for(int j=0;l+j<=n;j++){
            for(int k=0;l+j+k<=n;k++){
                if(j) ckmin(f[j-1][k][l+1],f[j][k][l]);
                ckmin(f[k+j][j][l],f[j][k][l]+s[l+1]);
            }
        }
    }
    printf("%d",f[0][0][n]);
}