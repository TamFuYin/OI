#include<bits/stdc++.h>
void ckmin(int& a,int b){if(b<a) a=b;}
void ckmax(int& a,int b){if(b>a) a=b;}
#define ALL(x) x.begin(),x.end()
const int N=4e5+10,B=700;
int a[N],a2[N];
struct qry{
    int l,r,x,y,k;
}b[N];
std::vector<int> b1,b2[B+1];
int bl[N];
bool cmp(int i1,int i2){
    return bl[b[i1].l]!=bl[b[i2].l]?bl[b[i1].l]<bl[b[i2].l]:b[i1].r<b[i2].r;
}
int ans[N];
int n,k;
int cnt[N];
std::basic_string<int> lis[N];//每块内，cnt=i 的元素的数量
int front[N];
void add(int x){
    if(!--lis[bl[x]][cnt[x]]&&cnt[x]==front[bl[x]])
        ++front[bl[x]];
    ++cnt[x];
    if(cnt[x]==(int)lis[bl[x]].size()) lis[bl[x]]+=0;
    ++lis[bl[x]][cnt[x]];
}
void dec(int x){
    --lis[bl[x]][cnt[x]];
    if(cnt[x]==front[bl[x]]) --front[bl[x]];
    --cnt[x];
    ++lis[bl[x]][cnt[x]];
}
int solve(int l,int r){
    int ans=INT_MAX;
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++) ckmin(ans,cnt[i]);
    }
    else{
        for(int i=l;bl[i]==bl[l];i++) ckmin(ans,cnt[i]);
        for(int i=r;bl[i]==bl[r];i--) ckmin(ans,cnt[i]);
        for(int i=bl[l]+1;i<bl[r];i++) ckmin(ans,front[i]);
    }
    return ans==INT_MAX?0:ans;
}
int ap[N];
int b2l[N],b2r[N];
int main(){
    // freopen(".in","r",stdin);
    // freopen("ex_recall8.in","r",stdin);
    // freopen("ex_recall8.out","w",stdout);
    std::ios::sync_with_stdio(0);std::cin.tie(0);
    for(int i=1;i<N;i++) bl[i]=(i-1)/B;
    int q,C;std::cin>>n>>q>>C;
    for(int i=1;i<=n;i++) std::cin>>a[i];
    for(int i=1;i<=q;i++){
        std::cin>>b[i].l>>b[i].r>>b[i].x>>b[i].y>>b[i].k;
        b[i].x=(b[i].x+b[i].k-1)/b[i].k,b[i].y/=b[i].k;
        if(b[i].k>B) b1.push_back(i);
        else b2[b[i].k].push_back(i);
    }
    std::sort(ALL(b1),cmp);
    int l=1,r=0;
    for(int i:b1){
        while(r<b[i].r) ++cnt[a[++r]];
        while(l>b[i].l) ++cnt[a[--l]];
        while(r>b[i].r) --cnt[a[r--]];
        while(l<b[i].l) --cnt[a[l++]];
        ans[i]=INT_MAX;
        for(int j=b[i].x;j<=b[i].y;j++) ckmin(ans[i],cnt[j*b[i].k]);
        if(ans[i]==INT_MAX) ans[i]=0;
    }
    while(l<=r) --cnt[a[l++]];
    for(k=1;k<=B;k++)if(!b2[k].empty()){
        int n2=0,mx=0;
        for(int i=1;i<=n;i++) if(a[i]%k==0) a2[++n2]=a[i]/k,ap[n2]=i;
        for(int i=1;i<=n2;i++) ckmax(mx,a[i]);
        for(int i:b2[k])
            b2l[i]=std::lower_bound(ap+1,ap+n2+1,b[i].l)-ap,
            b2r[i]=std::upper_bound(ap+1,ap+n2+1,b[i].r)-ap-1;
        for(int i=0;i<=bl[mx];i++) lis[i]=B,front[i]=0;
        l=1,r=0;
        std::sort(ALL(b2[k]),cmp);
        for(int i:b2[k]){
            while(r<b2r[i]) add(a2[++r]);
            while(l>b2l[i]) add(a2[--l]);
            while(r>b2r[i]) dec(a2[r--]);
            while(l<b2l[i]) dec(a2[l++]);
            ans[i]=solve(b[i].x,b[i].y);
        }
        while(l<=r) dec(a2[l++]);
    }
    for(int i=1;i<=q;i++) std::cout<<ans[i]<<"\n";
    return 0;
}