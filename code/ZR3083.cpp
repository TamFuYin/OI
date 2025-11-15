#include<bits/stdc++.h>
const int N=1e5;
using uint=unsigned int;
uint a[N];
uint shift(uint x,int y){
    if(y<0) return x>>-y;
    else return x<<y;
}
#define U UINT32_MAX
struct function{
    uint s[63],b;
    function(){memset(s,0,sizeof s),b=0;}
    function(uint x):b(x){memset(s,0,sizeof s),s[31]=U;}
    function operator*(const function& g)const{
        function h;h.b=b;
        for(int i=-31;i<=31;i++){
            for(int j=-31;j<=31;j++)
                if(-31<=i+j&&i+j<=31)
                    h.s[31+i+j]^=g.s[31+j]&shift(s[31+i],-j);
            h.b^=shift(g.b&s[31+i],i);
        }
        return h;
    }
    function operator^(const function& g)const{
        function h;h.b=b^g.b;
        for(int i=-31;i<=31;i++) h.s[31+i]=s[31+i]^g.s[31+i];
        return h;
    }
    bool isI(){
        if(s[31]!=U||b!=0) return 0;
        for(int i=-31;i<=31;i++) if(i) if(s[31+i]!=0) return 0;
        return 1;
    }
    uint at(uint x)const{
        uint y=b;
        for(int i=-31;i<=31;i++)
            y^=shift(x&s[31+i],i);
        return y;
    }
    uint find(uint y)const{
        y^=b;uint x=0;
        while(y){
            for(int i=31;i>=0;i--){
                if(y>>i&1){
                    int t=-1;
                    for(int j=i;j>=-31;j--){
                        if(s[31+j]>>i-j&1){
                            t=i-j;
                            break;
                        }
                    }
                    if(t==-1) return -1;
                    x^=1u<<t;
                    for(int j=-31;j<=31;j++)
                        if(s[31+j]>>t&1) y^=1u<<t+j;
                }
            }
        }
        return x;
    }
    bool operator==(const function& g)const{
        for(int i=0;i<=62;i++) if(s[i]!=g.s[i]) return 0;
        return b==g.b;
    };
};
function t[N*4],tag[N*4];
int len[N*4];
int n;
void pushup(int o){
    t[o]=t[o<<1]^t[o<<1|1];
}
void push(int o,function f){
    t[o]=f*t[o];
    if(len[o]&1^1) t[o].b^=f.b;
    tag[o]=f*tag[o];
}
void pushdown(int o){
    if(!tag[o].isI()){
        push(o<<1,tag[o]);
        push(o<<1|1,tag[o]);
        tag[o]=0;
    }
    assert(t[o]==(t[o<<1]^t[o<<1|1]));
}
void build(int l=1,int r=n,int o=1){
    tag[o]=0;len[o]=r-l+1;
    if(l==r){
        t[o]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
    pushup(o);
}
void modify(int L,int R,function f,int l=1,int r=n,int o=1){
    if(L<=l&&r<=R) return push(o,f);
    int mid=l+r>>1;pushdown(o);
    if(L<=mid) modify(L,R,f,l,mid,o<<1);
    if(mid<R) modify(L,R,f,mid+1,r,o<<1|1);
    pushup(o);
}
function get(int L,int R,int l=1,int r=n,int o=1){
    if(L<=l&&r<=R) return t[o];
    int mid=l+r>>1;pushdown(o);function ret;
    if(L<=mid) ret=ret^get(L,R,l,mid,o<<1);
    if(mid<R) ret=ret^get(L,R,mid+1,r,o<<1|1);
    return ret;
}
void flash(int l=1,int r=n,int o=1){
    if(l==r) return;
    int mid=l+r>>1;
    pushdown(o);
    flash(l,mid,o<<1);
    flash(mid+1,r,o<<1|1);
    assert(t[o]==(t[o<<1]^t[o<<1|1]));
}
int main(){
    freopen(".err","w",stderr);
    // while(1){
    //     std::mt19937 rnd(time(0));
    //     auto rndf=[&](){
    //         function r;r.b=rnd();
    //         for(int i=-31;i<=31;i++) r.s[31+i]=rnd()&shift(U,-i);
    //         return r;
    //     };
    //     function f=rndf(),g=rndf(),h=rndf();
    //     assert(chkeq((f*g)*h,f*(g*h)));
    // }
    // freopen("ex_a2.in","r",stdin);
    // freopen(".out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int id,q;std::cin>>id>>n>>q;
    for(int i=1;i<=n;i++) std::cin>>a[i];
    build();
    // for(int i=1;i<=n;i++) t[i]=a[i];
    while(q--){
        int T,l,r;std::cin>>T>>l>>r;
        if(T==1){
            int k,p;function g(0);
            std::cin>>k>>g.b;
            while(k--) std::cin>>p,g.s[31+p]=shift(U,-p);
            modify(l,r,g);
            // for(int i=l;i<=r;i++) t[i]=g*t[i];
        }
        else{
            function f=get(l,r);
            // function f={0,0};
            // for(int i=l;i<=r;i++) f=f^t[i];
            uint x;std::cin>>x;
            std::cout<<(T==2?f.at(x):f.find(x))<<std::endl;
        }
        // flash();
        // puts("!");
    }
}