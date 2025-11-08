#define DEBUG
#ifdef DEBUG
#include<bits/stdc++.h>
namespace CF{
    struct buf{
        char _[1<<22],*begin,*end;
        buf():begin(_),end(_){}
        template<typename... Args>
        void write(Args... args){
            end+=sprintf(end,args...);
        }
        template<typename... Args>
        int read(const char s[],Args... args){
            while(begin<end&&isspace(*begin)) ++begin;
            if(begin==end){
                begin=end=_;
                return -1;
            }
            int len=0,ret=
            sscanf(begin,(std::string(s)+"%n").c_str(),args...,&len);
            begin+=len;
            if(begin-_>(1<<20)){
                std::copy(begin,end,_);
                end-=begin-_;
                begin=_;
            }
            return ret;
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
        while(out.read("%s",s)>0){
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
    }
    __attribute__((constructor))
    void init(){
        T=100;
        in.write("%d\n",T);
        _init();
    }
    #define scanf(s,...) CF::in.read(s,__VA_ARGS__)
    #define printf(...) CF::out.write(__VA_ARGS__)
    #define puts(s) CF::out.write((std::string(s)+'\n').c_str())
    #define fflush(stdout) CF::work()
}
#endif