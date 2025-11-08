#include<bits/stdc++.h>
#define DEBUG
#ifdef DEBUG
namespace CF{
    struct buf{
        char _[1<<22],*begin,*end;
        buf():begin(_),end(_){}
        template<typename... Args>
        void write(Args... args){
            end+=sprintf(end,args...);
        }
        template<typename... Args>
        void read(const char s[],Args... args){
            int len=0;
            sscanf(begin,(std::string(s)+"%n").c_str(),args...,&len);
            begin+=len;
            if(begin-_>(1<<20)){
                std::copy(begin,end,_);
                end-=begin-_;
                begin=_;
            }
        }
    }out,in;
    std::vector<int> p;
    // std::mt19937 rnd(time(0));
    std::mt19937 rnd(0);
    int n,k,T;
    int qt;
    void _init(){
        n=300,k=rnd()%n+1;
        p.clear();
        for(int i=1;i<=n;i++){
            p.push_back(i);
            if(i!=k) p.push_back(i);
        }
        std::shuffle(p.begin(),p.end(),rnd);
        in.write("%d\n",n);qt=0;
    }
    void work(){
        char s[3];
        out.read("%s",s);
        if(s[0]=='?'){
            bool ret=0;
            int x,m,k;out.read("%d%d",&x,&m);
            while(m--) out.read("%d",&k),ret|=p[k-1]==x;
            in.write("%d\n",ret);
            ++qt;
        }
        else{
            assert(s[0]=='!');
            int x;out.read("%d",&x);
            assert(x==k);
            fprintf(stderr,"ANSWER CORRECT! QUREY TIME = %d\n",qt);
            if(--T) _init();
        }
    }
    __attribute__((constructor))
    void init(){
        T=10;
        in.write("%d\n",T);
        _init();
    }
    #define scanf(s,...) CF::in.read(s,__VA_ARGS__)
    #define printf(...) CF::out.write(__VA_ARGS__)
    #define puts(s) CF::out.write((std::string(s)+'\n').c_str())
    #define fflush(stdout) CF::work()
}
#endif
const int N=1e5+10;
int bh[N];
bool ask(int x,int L,int R){
    printf("? %d %d ",x,R-L+1);
    for(int i=L;i<=R;i++) printf("%d ",bh[i]);
    puts("");fflush(stdout);
    int b;scanf("%d",&b);
    return b;
}
std::vector<int> tl,tr;
#define ALL(x) x.begin(),x.end()
void solve(int L,int R,const std::vector<int>& a,const std::vector<int>& s){
    assert(!a.empty());
    assert(a.size()*2-1+s.size()==R-L+1);
    if(a.size()==1){
        printf("! %d\n",a[0]);
        fflush(stdout);
        return;
    }
    int mid=L+R>>1;
    std::vector<int> la,ra,ls,rs;
    for(int i:s){
        if(ask(i,L,mid)) ls.push_back(i);
        else rs.push_back(i);
    }
    for(int i:a){
        if(ask(i,L,mid)){
            if(ask(i,mid+1,R)) ls.push_back(i),rs.push_back(i);
            else la.push_back(i);
        }
        else ra.push_back(i);
    }
    if(mid-L+1-ls.size()&1) assert(R-mid-rs.size()&1^1),solve(L,mid,la,ls);
    else assert(R-mid-rs.size()&1),solve(mid+1,R,ra,rs);
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        static std::mt19937 rnd(time(0));
        int m=2*n-1;
        std::iota(bh+1,bh+m+1,1);
        // std::shuffle(bh+1,bh+m+1,rnd);
        std::vector<int> p(n);
        std::iota(ALL(p),1);
        solve(1,m,p,std::vector<int>());
    }
}