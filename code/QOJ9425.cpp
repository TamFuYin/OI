#include<bits/stdc++.h>
const int N=1e5;
struct SA{
    void make(std::string s){
    }
    int LCP(int x,int y){}
}sa1,sa2;
struct trie{
}t1,t2;
std::vector<std::pair<int,int> > strs[N];
int cnt;
int main(){
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int n,q;std::string s;
    std::cin>>n>>q>>s;
    sa1.make(s),std::reverse(s.begin(),s.end()),sa2.make(s);
    while(q--){
        std::string op;int k,l,r;
        std::cin>>op;
        if(op=="+"){
            std::cin>>k;++cnt;
            while(k--) std::cin>>l>>r,strs[cnt].emplace_back(l,r);
        }
        else if(op=="-"){
            std::cin>>k;
        }
    }
}