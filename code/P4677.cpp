using ll=long long;
struct point{
    int x;ll y;
    bool operator<(const point& b)const{
        return y<b.y||y==b.y&&x<b.x;
    }
};
struct vector{
    int x;ll y;
    vector operator+(const vector& b)const{
        return {x+b.x,y+b.y};
    }
};
point operator+(const point& a,const vector& b){
    return {a.x+b.x,a.y+b.y};
}
ll operator*(const vector& a,const vector& b){
    return a.x*b.y-a.y*b.x;
}
vector operator-(const point& a,const point& b){
    return {a.x-b.x,a.y-b.y};
}
#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,const T& b){if(b<a) a=b;}
const int N=5e5+10;
int a[N];
ll s[N];
int n,m;
point f[N];
int pl[N],pr[N];
point solve(ll k){
    auto w=[&k](int j,int i){
        int mid=(i+j+1)/2;
        return f[j]+vector{1,s[i]+s[j]-2*s[mid]+(ll)a[mid]*(2*mid-j-i)-k};
    };
    std::deque<int> q;
    q.push_back(0);
    pl[0]=1;pr[0]=n;
    f[0]={0,0};
    for(int i=1;i<=n;i++){
        while(!q.empty()&&i>pr[q.front()]) q.pop_front();
        assert(!q.empty());//it never become empty
        f[i]=w(q.front(),i);
        assert(pl[q.front()]==i);
        ++pl[q.front()];
        while(!q.empty()&&w(i,pl[q.back()])<w(q.back(),pl[q.back()])){
            q.pop_back();
            if(!q.empty()) pr[q.back()]=n;
        }
        if(q.empty()) q.push_back(i),pl[i]=i+1,pr[i]=n;
        else{
            if(!(w(i,n)<w(q.back(),n))) continue;
            int left=std::max(pl[q.back()],i+1),right=n;
            while(left<right){
                int mid=left+right>>1;
                if(w(i,mid)<w(q.back(),mid)) right=mid;
                else left=mid+1;
            }
            pr[q.back()]=left-1;
            pl[i]=left;pr[i]=n;
            q.push_back(i);
        }
        assert(pr[q.back()]==n);
    }
    f[n].y+=f[n].x*k;
    return f[n];
}
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    a[1]=0;
    for(int i=2;i<=n;i++) scanf("%d",a+i),a[i]+=a[i-1];
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    solve(-10);
    ll left=-1e12,right=0;
    while(left<right){
        ll mid=left+(right-left+1)/2;
        if(solve(mid).x<=m) left=mid;
        else right=mid-1;
    }
    point l=solve(left),r=solve(left+1);
    assert(l.x<=m&&m<=r.x);
    assert(r.y-l.y==left*(r.x-l.x));
    if(l.x==r.x) printf("%lld\n",l.y);
    else printf("%lld\n",l.y+(m-l.x)*left);
}