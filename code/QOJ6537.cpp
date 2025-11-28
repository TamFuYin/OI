#include<bits/stdc++.h>
const std::vector<std::pair<std::string,std::vector<std::string>>> trans[3]={{
    {"CB",{"01$"}},
    {"CBAB",{"01$","23"}},
    {"CAB",{"02$","1"}},
    {"ACB",{"02","1$"}},
    {"C",{"0$"}},
    {"",{"$"}}
},{
    {"A",{"0$"}},
    {"C",{"0$"}},
    {"ACB",{"02","1$"}},
    {"CAB",{"02","1$"}},
    {"AC",{"01$"}},
    {"CA",{"01$"}},
    {"ABC",{"012$"}},
    {"CBA",{"012$"}}
},{
    {"AB",{"01$"}},
    {"ABCB",{"01$","23"}},
    {"ACB",{"02$","1"}},
    {"CAB",{"02","1$"}},
    {"A",{"0$"}},
    {"",{"$"}}
}};
std::map<std::string,std::vector<std::basic_string<int>>> S;
int main(){
    S[""].push_back({});
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a;scanf("%d",&a);--a;
        for(auto [s,ns]:trans[a]){
            if(s.empty()||!S[s].empty()){
                auto& u=S[s].back();
                for(auto t:ns){
                    std::string nt;
                    std::basic_string<int> v;
                    for(int j=0;j<t.size();j++)
                        if(t[j]=='$') v+=i,nt+='A'+a;
                        else v+=u[t[j]-'0'],nt+=s[t[j]-'0'];
                    S[nt].push_back(v);
                }
                if(!s.empty()) S[s].pop_back();
                break;
            }
        }
    }
    int ans=S["ABC"].size()+S["CBA"].size()+S["ABCB"].size()+S["CBAB"].size();
    printf("%d\n",ans);
    for(auto& v:S["ABC"])
        printf("%d %d %d\n",v[0],v[1],v[2]);
    for(auto& v:S["CBA"])
        printf("%d %d %d\n",v[0],v[1],v[2]);
    for(auto& v:S["ABCB"])
        printf("%d %d %d\n",v[0],v[1],v[2]);
    for(auto& v:S["CBAB"])
        printf("%d %d %d\n",v[0],v[1],v[2]);
    return 0;
}