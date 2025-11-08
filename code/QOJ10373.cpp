#include<bits/stdc++.h>
int main(){
    int sum=0;
    for(int id=1;id<=8;id++){
        freopen(("QOJ10373\\"+std::to_string(id)+".in").c_str(),"r",stdin);
        int n,m,p;scanf("%d%d%d",&n,&m,&p);
        sum+=p;
    }
    printf("%d\n",sum);
}