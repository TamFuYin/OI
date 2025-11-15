#include<bits/stdc++.h>
const int N=32;
std::string s[N];
int v[N];
using ll=long long;
int n;
std::string cap(const std::string& s,const std::string& t){
    std::string ret(n,0);
    for(int i=0;i<n;i++){
        if(s[i]!='?'&&t[i]!='?'&&s[i]!=t[i]) return "";
        if(s[i]=='?') ret[i]=t[i];
        else ret[i]=s[i];
    }
    return ret;
}
int dim(const std::string& s){
    int ret=0;
    for(int i=0;i<n;i++) ret+=s[i]=='?';
    return ret;
}
std::string backslash(const std::string& s,std::string t){
    for(int i=0;i<n;i++){
        if(s[i]=='?'&&t[i]!='?'){
            t[i]='0'+'1'-t[i];
            break;
        }
    }
    return t;
}
ll f(std::string S,int i){
    if(i==-1) return 0;
    auto c=cap(S,s[i]);
    if(!c.length()) return f(S,i-1);
    int cd=dim(c),sd=dim(S);
    if(cd<=sd-2) return f(S,i-1)-f(c,i-1)+(1ll*v[i]<<cd);
    else if(cd==sd-1) return f(backslash(S,c),i-1)+(1ll*v[i]<<cd);
    else {assert(cd==sd);return 1ll*v[i]<<cd;}
}
int main(){
    // freopen("remember3.in","r",stdin);
    // freopen("remember.out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int m;std::cin>>n>>m;
    for(int i=0;i<m;i++) std::cin>>s[i]>>v[i];
    printf("%lld\n",f(std::string(n,'?'),m-1));
}