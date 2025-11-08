#include<bits/stdc++.h>
const int N=1e5+10;
template<typename T>
void ckmin(T &x,T y){
    x=std::min(x,y);
}
template<typename T>
void ckmax(T &x,T y){
    x=std::max(x,y);
}
int p[N];
struct data{
    int v,cl,cr;
    data(int v=0,int cl=0,int cr=0):v(v),cl(cl),cr(cr){}
    bool empty(){
        return v==0;
    }
    bool operator==(const data& b)const{
        return cl==b.cl&&cr==b.cr;
    }
    void ck(const data& b){
        if(b.v>v) *this=b;
        else if(b.v==v) ckmin(cl,b.cl),ckmax(cr,b.cr);
    }
    data operator-(int x)const{
        return {v-x,cl+1,cr+1};
    }
};
int n;
namespace BIT{
    data t[N];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x,data v){
        while(x<N){
            t[x].ck(v);
            x+=lowbit(x);
        }
    }
    data ask(int x){
        data ret;
        while(x){
            ret.ck(t[x]);
            x-=lowbit(x);
        }
        return ret;
    }
    void clear(){
        memset(t,0,sizeof t);
    }
}
data solve(int k){
    data ret;
    BIT::clear();
    for(int i=1;i<=n;i++){
        data fi=BIT::ask(p[i]);
        fi.ck(BIT::ask(n)-k);
        ++fi.v;
        BIT::add(p[i],fi);
        ret.ck(fi);
    }
    return ret;
}
int ans[N];
data pk[N];
void wqs(int L,int R){
    if(pk[L].empty()) pk[L]=solve(L);
    if(pk[R].empty()) pk[R]=solve(R);
    if(pk[L]==pk[R]) return;
    int mid=L+R>>1;
    wqs(L,mid),wqs(mid+1,R);
}
int main(){
    // freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",p+i);
        for(int i=0;i<=n;i++) pk[i]=data(),ans[i]=0;
        wqs(0,n);
        for(int i=0;i<=n;i++) if(!pk[i].empty()){
            for(int j=pk[i].cl;j<=pk[i].cr;j++) ckmax(ans[j],pk[i].v+i*j);
            // printf("%d %d [%d,%d]\n",i,pk[i].v,pk[i].cl,pk[i].cr);
        }
        for(int i=1;i<n;i++) ckmax(ans[i],ans[i-1]);
        for(int i=0;i<n;i++) printf("%d ",ans[i]);puts("");
    }
}