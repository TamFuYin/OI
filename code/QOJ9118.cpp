/*

最神秘

用 $\mathbb F_2[x]$ 的多项式环来解释这个操作。

那么相当于每次 $f\gets xf\bmod f_a$，其中 $f_a=1+x^n+\sum_ix^{A_i-1}$。

然后可以选择 $f\gets f+f_b$，其中 $f_b=\sum_i x^{B_i-1}$。

我们记 $f_u=\sum_{i=0}^{M-1}u_ix^{M-1-i}$ 为可以任取的度数 $<M$ 的多项式，那么相当于最小化 $M$，使得 $x^Mf_s+f_bf_u\equiv f_t\pmod {f_a}$。

我们不妨记作 $f_bf_u+f_af_v=x^Mf_s+f_t$，发现是一个丢番图方程，有解当且仅当 $\gcd(f_a,f_b)|(x^Mf_s+f_t)$，而且可以用拓展欧几里得算法得到一组特解。

记 $f_g=\gcd(f_a,f_b)$，则令 $f_u$ 为在 $f_a/f_g$ 的同余系中度数最小的解。如果 $\deg f_u<M$，那么这个 $M$ 就是好的。

$\mathbb F_2$ 的多项式操作可以用 bitset 加速，所以实际上会比较快？

可以更相减损术。每次用度数较小的一项消掉度数较大的一项，可能比直接写多项式取模快？

不难发现更相减损也是可以 exgcd 的。

但是我们的问题是：`std::bitset` 不支持 highest bit……

所以只好手写了。

写了 200 多行。是不是可以挂 github 骗 star 了？
*/
#include<bits/stdc++.h>
template<typename T>
int lowbit(T x){
    return __builtin_ctzll(x);
}
struct bitset{
    static const int N=3e4;
    using ull=unsigned long long;
    std::valarray<ull> a;
    struct iterator{
        int i,b;const bitset* a;
        iterator operator++(){
            if(b==63||a->a[i]<(1ull<<b+1)){
                do++i;while(i<N&&!a->a[i]);
                if(i==N) return *this=a->end();
                return *this={i,lowbit(a->a[i]),a};
            }
            return *this={i,lowbit(a->a[i]>>b+1)+b+1,a};
        }
        bool operator==(const iterator& it)const{
            return a==it.a&&i==it.i&&b==it.b;
        }
        bool operator!=(const iterator& it)const{
            return !(*this==it);
        }
        int operator*()const{
            return i<<6|b;
        }
    };
    iterator end()const{
        return {N,0,this};
    }
    iterator begin()const{
        int i=0;
        while(i<N&&!a[i]) ++i;
        if(i==N) return end();
        return {i,lowbit(a[i]),this};
    }
    bitset(int x=0){
        a.resize(N);a=0;
        a[0]=x;
    }
    void set(int x){
        a[x>>6]|=1ull<<(x&63);
    }
    void flip(int x){
        a[x>>6]^=1ull<<(x&63);
    }
    void reset(int x){
        set(x),flip(x);
    }
    bitset operator+(const bitset& b)const{
        bool res=0;
        bitset c;
        for(int i=0;i<N;i++) c.a[i]=a[i]^b.a[i]^res,res=((int)a[i]+b.a[i]+res)/2;
        assert(!res);
        return c;
    }
    bool operator<(const bitset& b)const{
        for(int i=N-1;i>=0;i--)
            if(a[i]<b.a[i]) return 1;
            else if(b.a[i]<a[i]) return 0;
        return 0;
    }
    bool operator<=(const bitset& b)const{
        return !(b<*this);
    }
    bitset operator-(const bitset& b)const{
        bitset c;
        bool res=0;
        for(int i=0;i<N;i++) c.a[i]=a[i]^b.a[i]^res,res=a[i]<(int)b.a[i]+res;
        return c;
    }
    bitset operator<<(int k)const{
        if(k==0) return *this;
        bitset c;c=0;
        for(int i=0;i+(k>>6)<N;i++){
            c.a[i+(k>>6)]|=a[i]<<(k&63);
            if(i+(k>>6)+1<N&&(k&63)) c.a[i+(k>>6)+1]|=a[i]>>64-(k&63);
        }
        return c;
    }
    bitset operator^(const bitset& b)const{
        bitset c;
        for(int i=0;i<N;i++) c.a[i]=a[i]^b.a[i];
        return c;
    }
    bitset operator&(const bitset& b)const{
        bitset c;
        for(int i=0;i<N;i++) c.a[i]=a[i]&b.a[i];
        return c;
    }
    bitset operator|(const bitset& b)const{
        bitset c;
        for(int i=0;i<N;i++) c.a[i]=a[i]|b.a[i];
        return c;
    }
    bitset& operator^=(const bitset& b){
        for(int i=0;i<N;i++) a[i]^=b.a[i];
        return *this;
    }
    bitset& operator&=(const bitset& b){
        for(int i=0;i<N;i++) a[i]&=b.a[i];
        return *this;
    }
    bitset& operator|=(const bitset& b){
        for(int i=0;i<N;i++) a[i]|=b.a[i];
        return *this;
    }
    int highest()const{
        for(int i=N-1;i>=0;i--) if(a[i]) return 64-__builtin_clzll(a[i])+(i<<6)-1;
        return -1;
    }
    bool empty()const{
        return highest()==-1;
    }
    void clear(){
        for(int i=0;i<N;i++) a[i]=0;
    }
    bool operator[](int x)const{
        return a[x>>6]>>(x&63)&1;
    }
    bool operator==(const bitset& b)const{
        for(int i=0;i<N;i++) if(a[i]!=b.a[i]) return 0;
        return 1;
    }
    bitset operator/(const bitset& b)const{
        bitset c,ret;c=*this,ret=0;
        int k=b.highest();
        while(c.highest()>=k) ret.set(c.highest()-k),c^=b<<(c.highest()-k);
        return ret;
    }
    void operator/=(const bitset& b){
        (*this)=(*this)/b;
    }
    bitset operator%(const bitset& b)const{
        bitset c;c=*this;
        int k=b.highest();
        while(c.highest()>=k) c^=b<<(c.highest()-k);
        return c;
    }
    bool div(const bitset& b)const{//整除
        return (b%(*this)).empty();
    }
    void operator%=(const bitset& b){
        (*this)=(*this)%b;
    }
    bitset operator*(const bitset& b)const{
        bitset c;c=0;
        for(auto i:b) c^=(*this)<<i;
        return c;
    }
    void operator*=(const bitset& b){
        (*this)=(*this)*b;
    }
    bitset div2_ceil()const{
        bitset c=*this;
        int i=0;
        while(c.a[i]) c.a[i++]=0;
        c.a[i]=1;
        for(int i=0;i<N-1;i++) c.a[i]=c.a[i+1];
        c.a[N-1]=0;
        return c;
    }
    int lg_ceil()const{
        int i=N-1;
        while(!a[i]) --i;
        for(int j=0;j<i;j++) if(a[j]) return i+1;
        return i;
    }
    friend std::istream& operator>>(std::istream& is,bitset& b){
        static std::string s;is>>s;
        for(int i=0;i<N&&(i<<6)<s.length();i++)
            for(int j=0;j<64&&(i<<6|j)<s.length();j++)
                b.a[i]|=ull(s[i<<6|j]=='1')<<j;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os,bitset& b){
        int k=b.highest();
        for(int i=0;i<=k;i++) os<<b[i];
        return os;
    }
    friend bitset exgcd(bitset a,bitset b,bitset& x,bitset& y){//在此处 segmentation fault？
        bitset &x1=x,&x2=y;x1=1,x2=0;
        bitset x3,x4;x3=0,x4=1;
        while(!b.empty()){
            bitset c=a/b;
            std::swap(a,b),b^=a*c;
            std::swap(x1,x3),x3^=x1*c;
            std::swap(x2,x4),x4^=x2*c;
        }
        return a;
    }
};
bitset S,T,A,B;
bitset C,u,v,g;
int main(){
    // freopen(".in","r",stdin);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int N,P,Q;std::cin>>N>>S>>T>>P;
    for(int i=1,a;i<=P;i++) std::cin>>a,A.set(a-1);
    A.flip(0);A.flip(N);std::cin>>Q;
    for(int i=1,b;i<=Q;i++) std::cin>>b,B.set(b-1);
    int M;
    for(M=1;;M++){
        if(M>1000){
            puts("-1");
            return 0;
        }
        g=exgcd(A,B,v,u);
        C=(S<<M)^T;
        if(!g.div(C)) continue;
        // assert(((A*v)^(B*u))==g);
        u*=C/g;
        // v*=C/g,assert(((A*v)^(B*u))==C);
        // bitset k=u/(A/g);
        u%=A/g;
        // v^=k*(B/g),assert(((A*v)^(B*u))==C);
        if(u.highest()<M) break;
    }
    printf("%d\n",M);
    // bitset b=((B*u)^(S<<M))%A;
    // std::cerr<<"A: "<<A<<"\nB: "<<B<<"\nC: "<<C<<"\nu: "<<u<<"\nv: "<<v<<"\nS: "
    // <<S<<"\nT: "<<T<<"\nb: "<<b<<'\n';
    // assert(b==T%A);
    for(int i=M-1;i>=0;i--) printf("%d",(int)u[i]);
}