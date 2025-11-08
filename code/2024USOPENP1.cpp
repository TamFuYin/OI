#include<bits/stdc++.h>
using ll=long long;
using pii=std::pair<ll,int>;
std::priority_queue<pii,std::vector<pii>,std::greater<pii> > hp;
const int N=1e6+10;
int t[N];
int fa[N],rnk[N];
int findp(int x){
    return fa[x]=fa[x]==x?x:findp(fa[x]);
}
void merge(int x,int y){
    x=findp(x),y=findp(y);
    if(x==y) return;
    if(rnk[x]<rnk[y]) std::swap(x,y);
    fa[y]=x;
    if(rnk[x]==rnk[y]) ++rnk[x];
}
int main(){
    int n,k;scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=1;i<=k;i++) hp.push(std::make_pair((ll)t[i],i)),rnk[fa[i]=i]=0;
    for(int i=k+1;i<=n;){
        pii cur=hp.top();
        while(!hp.empty()&&hp.top().first==cur.first){
            merge(hp.top().second,cur.second);
            hp.pop();
            if(i<=n) hp.push(std::make_pair(cur.first+t[i++],cur.second));
            else{
                while(!hp.empty()&&hp.top().first==cur.first){
                    merge(hp.top().second,cur.second);
                    hp.pop();
                }
                printf("%lld\n",cur.first);
                for(int j=1,x=findp(cur.second);j<=k;j++) printf("%d",findp(j)==x);
                return 0;
            }
        }
    }
    pii cur=hp.top();
    while(!hp.empty()&&hp.top().first==cur.first){
        merge(hp.top().second,cur.second);
        hp.pop();
    }
    printf("%lld\n",cur.first);
    for(int i=1,x=findp(cur.second);i<=k;i++) printf("%d",findp(i)==x);
    return 0;
}
