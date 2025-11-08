// 通用测评，前进四！
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,T b){a=std::min(a,b);}
const int N=1e6+10;
std::basic_string<std::pair<int,int> > his[N],quer[N];
int T;
struct node{
    int max,sec,maxcnt;//最大值被成功 check min 成功过多少次，标记永久化就成了数据
    int ckmin;//ckmin 标记
}t[N*4];
void pushup(int o){
    if(t[o<<1].max==t[o<<1|1].max)
        t[o].max=t[o<<1].max,
        t[o].sec=std::max(t[o<<1].sec,t[o<<1|1].sec);
    else if(t[o<<1].max>t[o<<1|1].max)
        t[o].max=t[o<<1].max,
        t[o].sec=std::max(t[o<<1].sec,t[o<<1|1].max);
    else
        t[o].max=t[o<<1|1].max,
        t[o].sec=std::max(t[o<<1|1].sec,t[o<<1].max);
}
void pushdown(int o){
    if(t[o].ckmin!=INT_MAX){
        if(t[o<<1].max>=t[o<<1|1].max) t[o<<1].max=t[o<<1].ckmin=t[o].ckmin;
        if(t[o<<1|1].max>=t[o<<1].max) t[o<<1|1].max=t[o<<1|1].ckmin=t[o].ckmin;
        t[o].ckmin=INT_MAX;
    }
    if(t[o].maxcnt){
        if(t[o<<1].max==t[o].max) t[o<<1].maxcnt+=t[o].maxcnt;
        if(t[o<<1|1].max==t[o].max) t[o<<1|1].maxcnt+=t[o].maxcnt;
        t[o].maxcnt=0;
    }
}
void subckmin(int o,int v){
    if(v>=t[o].max) return;
    if(t[o].sec<v&&v<t[o].max){
        ++t[o].maxcnt;
        t[o].max=v;
        t[o].ckmin=v;
        return;
    }
    pushdown(o);
    subckmin(o<<1,v);
    subckmin(o<<1|1,v);
    pushup(o);
}
void ckmin(int L,int R,int v,int l=1,int r=T,int o=1){
    if(L>R) return;
    if(L<=l&&r<=R) return subckmin(o,v);
    int mid=l+r>>1;
    pushdown(o);
    if(L<=mid) ckmin(L,R,v,l,mid,o<<1);
    if(mid<R) ckmin(L,R,v,mid+1,r,o<<1|1);
    pushup(o);
}
int query(int x,int l=1,int r=T,int o=1){
    if(l==r) return t[o].maxcnt;
    int mid=l+r>>1;pushdown(o);
    if(x<=mid) return query(x,l,mid,o<<1);
    else return query(x,mid+1,r,o<<1|1);
}
void build(int l=1,int r=T,int o=1){
    t[o].max=INT_MAX,t[o].sec=-1,t[o].maxcnt=0;
    t[o].ckmin=INT_MAX;
    if(l==r) return;
    int mid=l+r>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
}
int ans[N];
int main(){
    std::cin.tie(0);std::ios::sync_with_stdio(0);
    int n,Q=0;std::cin>>n>>T;
    for(int i=1,ai;i<=n;i++) std::cin>>ai,his[i]+=std::make_pair(1,ai);
    for(int i=1;i<=T;i++){
        int type,x;std::cin>>type>>x;
        if(type==1){
            int v;std::cin>>v;
            his[x]+=std::make_pair(i,v);
        }
        else{
            quer[x]+=std::make_pair(i,++Q);
        }
    }
    build();
    for(int i=n;i>=1;i--){
        for(int j=0;j<his[i].size();j++){
            int r=j==his[i].size()-1?T:his[i][j+1].first-1;
            ckmin(his[i][j].first,r,his[i][j].second);
        }
        for(auto p:quer[i]) ans[p.second]=query(p.first);
    }
    for(int i=1;i<=Q;i++) std::cout<<ans[i]<<"\n";
}