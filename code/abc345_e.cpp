#include<bits/stdc++.h>
const int N=1e5;
int c[N],v[N],last[N],next[N];
typedef std::pair<int,int> pii;
std::priority_queue<pii,std::vector<pii>,std::greater<pii> > hp,hp2;
int n,k;
int getdel(){
    if(k==1||hp2.empty()) return hp.empty()?-1:hp.top().second;
}
int main(){
    scanf("%d%d",&n,&k);pii mx;int head;
    for(int i=1,begin,ls=0,len;i<=n;i++){
        scanf("%d%d",&c[i],&v[i]);
        if(c[i]!=c[i-1]) begin=i,mx={v[i],i},len=1;
        else mx=std::max(mx,std::make_pair(v[i],i)),++len;
        if(c[i]!=c[i+1]) next[last[mx.second]=ls]=mx.second,ls=mx.second,k-=len-1,head=ls?head:mx.second;
    }
    if(k<0) {printf("-1");return 0;}
    for(int i=head;i;i=next[i]){
        if(c[last[i]]==c[next[i]]) hp2.push({v[i]+std::min(v[last[i]],v[next[i]]),i});
        else hp.push({v[i],i});
    }
    while(k){
    }
}