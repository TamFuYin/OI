#include<bits/stdc++.h>
using i128=__int128;
std::istream& operator>>(std::istream& in,i128& x){
    std::string s;in>>s;
    x=0;for(char i:s) x=x*10+i-'0';
    return in;
}
std::set<int> acc;
const int N=31;
int qd[N];
int n,b;
i128 f[2][N][N*N];
i128 solve(int yqd){
    static std::set<std::pair<int,bool> > ac;
    for(int i=1;i<=n;i++) ac.emplace(i,0),ac.emplace(i,1);
    for(int i=1;i<=yqd;i++) ac.erase({i,0}),ac.erase({qd[i],1});
    bool cur=0;f[0][0][0]=1;
    int prec[2]={0,0},sum=0;
    for(auto p:ac){
        cur^=1;sum+=p.first;
        ++prec[p.second];
        for(int j=0;j<=std::min(prec[0],prec[1]);j++){
            for(int k=0;k<=n*(n+1);k++){
                f[cur][j][k]=j<=std::min(prec[0]-(p.second==0),prec[1]-(p.second==1))?f[cur^1][j][k]:0;
                if(j&&k>=p.first)
                    f[cur][j][k]+=f[cur^1][j-1][k-p.first]*(prec[!p.second]-(j-1));
                // if((int)f[cur][j][k])
                //     printf("f[(%d, %d), %d, %d] = %d\n",p.first,(int)p.second,j,k,(int)f[cur][j][k]);
            }
        }
    }
    // printf("%d %d %d\n",prec[0],prec[1],(int)ac.size());
    // printf(">>> %d %d\n",(int)ac.size()/2,(b+sum)/2);
    return f[cur][ac.size()/2][(b+sum)/2];
}
int main(){
    // freopen(".in","r",stdin);
    i128 k;
    std::cin>>n>>b>>k;
    for(int i=1;i<=n;i++) acc.insert(i);
    for(int i=1;i<=n;i++){
        for(int j:acc){
            qd[i]=j;b-=std::abs(i-j);
            i128 cnt=solve(i);
            if(cnt<k) k-=cnt;
            else{
                acc.erase(j);
                break;
            }
            b+=std::abs(i-j);
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",qd[i]);
}