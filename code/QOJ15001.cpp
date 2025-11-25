#include<bits/stdc++.h>
#include<immintrin.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
typedef unsigned long long ull;
const int B=1<<20;
struct matrix{
    ull a[64];//存储列向量
    matrix(){
        memset(a,0,sizeof(a));
    }
    matrix operator*(const matrix& b)const{
        matrix c;
        for(int j=0;j<64;j++){
            c.a[j]=0;
            for(int k=0;k<64;k++)
                if(b.a[j]>>k&1) c.a[j]^=a[k];
        }
        return c;
    }
    ull operator*(ull b)const{
        ull c=0;
        for(int i=0;i<64;i++)
            if(b>>i&1) c^=a[i];
        return c;
    }
};
const matrix next=[](){
    matrix c;
    for(int i=0;i<64;i++){
        ull x=1ull<<i;
        x^=x<<13,x^=x>>17,x^=x<<5;
        c.a[i]=x;
    }
    return c;
}();
const matrix nextB=[](){
    matrix c=next;
    for(int i=0;i<std::__lg(B)+1;i++) c=c*c;
    return c;
}();
inline ull& gnext(ull& x){
    return x=next*x;
}
const int N=1e9;
ull seeds[N/B];
ull ans[N/B];
int main(){
    int n;ull seed;
    scanf("%d%llu",&n,&seed);
    int q=n/B,r=n%B;
    seeds[0]=seed;
    for(int i=1;i<q;i++) seeds[i]=nextB*seeds[i-1];
    ull tot=0;ull rseed=q==0?seed:nextB*seeds[q-1];
    for(int i=0;i<r;i++){
        ull x=gnext(rseed);
        int k=(gnext(rseed)&63)+1;
        ull p=_pdep_u64(1ull<<(k-1),x);
        tot+=_tzcnt_u64(p);
    }
    for(int i=0;i<B;i++){
        for(int j=0;j<q;j++){
            ull x=gnext(seeds[j]);
            int k=(gnext(seeds[j])&63)+1;
            ull p=_pdep_u64(1ull<<(k-1),x);
            ans[j]+=_tzcnt_u64(p);
        }
    }
    for(int i=0;i<q;i++) tot+=ans[i];
    printf("%llu\n",tot);
    return 0;
}