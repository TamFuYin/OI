#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){
    a=std::min(a,b);
}
template<typename T>
void ckmax(T& a,T b){
    a=std::max(a,b);
}
const int N=1e6+10;
int a[N],r[N],cnt[N];
double c[N];
int n,k;
namespace queue{
    struct data{
        int val;
        data *next,*prev;
    }_buf[N*2];
    data *begin[N],*end[N],*buf;
    bool empty(int c){
        // assert((begin[c]==end[c])==(begin[c]->next==0));//这里 assertion failed
        return begin[c]==end[c];
    }
    int& push(int c){
        data* it=end[c];
        end[c]=buf++;
        end[c]->next=0;
        it->next=end[c];
        end[c]->prev=it;
        return it->val;
    }
    void pop(int c){
        // assert(begin[c]!=end[c]);
        begin[c]=begin[c]->next;
    }
    int& front(int c){
        // assert(begin[c]!=end[c]);
        // assert(begin[c]!=0);
        return begin[c]->val;
    }
    int& back(int c){
        return end[c]->prev->val;
    }
    void clear(int c){
        begin[c]=end[c]=buf++;
        begin[c]->prev=begin[c]->next=0;
    }
}
using namespace queue;
bool check(double mid){
    std::fill(c+1,c+n+1,INFINITY);
    buf=_buf;
    for(int i=1;i<=n;i++) clear(i);
    for(int i=1;i<=n;i++){
        push(a[i])=i;
        while(!empty(a[i])&&i-front(a[i])+1>=k){
            int j=front(a[i]);pop(a[i]);
            ckmin(c[a[i]],r[j]-1-mid*(j-1));
        }
        if(r[i]-mid*i>=c[a[i]]) return 1;
        if(!empty(a[i])){
            int j=front(a[i]);
            if(r[i]-r[j]+1>=mid*k) return 1;
        }
    }
    return 0;
}
const double eps=1e-7;
int main(){
    freopen("mode5.in","r",stdin);
    // freopen("mode.out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    std::cin>>n>>k;
    int maj=0;
    double left=0,right=1;
    for(int i=1;i<=n;i++){
        std::cin>>a[i];
        r[i]=++cnt[a[i]];
        ckmax(maj,cnt[a[i]]);
        if(i==k) left=1.*maj/k;
    }
    while(right-left>eps){
        double mid=(left+right)/2;
        if(check(mid)) left=mid;
        else right=mid;
    }
    std::cout<<std::fixed<<std::setprecision(7)<<left;
}