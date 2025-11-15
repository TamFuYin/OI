#include<bits/stdc++.h>
auto ckmin=[](int& a,int b){a=std::min(a,b);};
const int N=2e5+10,V=2e5+1;
int a[N];
std::vector<int> p[N];
std::priority_queue<int> s;
int lsh[N],lcnt;
int l[N],r[N];
int main(){
    // freopen("eightyfour.in","r",stdin);
    // freopen("eightyfour.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,s;i<=n;i++)
        scanf("%d%d%d",&s,l+i,r+i),lsh[lcnt++]=l[i],lsh[lcnt++]=++r[i];
    std::sort(lsh,lsh+lcnt);
    lcnt=std::unique(lsh,lsh+lcnt)-lsh;
    for(int i=1;i<=n;i++)
        l[i]=std::lower_bound(lsh,lsh+lcnt,l[i])-lsh,
        r[i]=std::lower_bound(lsh,lsh+lcnt,r[i])-lsh,
        p[r[i]].push_back(l[i]);
    std::fill(a,a+V+1,n);
    for(int i=1,x,y;i<=m;i++)
        scanf("%d%d",&x,&y),
        x=std::lower_bound(lsh,lsh+lcnt,x)-lsh,
        ckmin(a[x],y);
    for(int i=1;i<=V;i++) ckmin(a[i],a[i-1]);
    int ans=n;
    for(int i=V;i>=1;i--){
        for(int j:p[i]) s.push(-j);
        while(s.size()>a[i]) p[-s.top()].push_back(0),s.pop(),--ans;
    }
    printf("%d\n",ans);
}