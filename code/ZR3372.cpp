#include<bits/stdc++.h>
const int N=1e6;
int tr[N][26],size;
void insert(std::string& s){
    int p=0;
    for(char i:s){
        if(!tr[p][i-'a']) tr[p][i-'a']=++size;
        p=tr[p][i-'a'];
    }
}
std::queue<int> q,q2;
int main(){
    // freopen("05.in","r",stdin);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
    int n;std::cin>>n;
    while(n--){
        std::string s;
        std::cin>>s;
        insert(s);
    }
    std::string t;
    std::cin>>t;
    q.push(0);
    int p=0;
    std::string ans;
    for(char ti:t){
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int c=0;c<26;c++) if(tr[u][c]){
                if(c==ti-'a') q2.push(tr[u][c]);
                else q.push(tr[u][c]),ans+='a'+c;
            }
        }
        if(q2.empty()){
            std::cout<<"YES\n"+ans;
            return 0;
        }
        ans+=ti;
        std::swap(q,q2);
    }
    std::cout<<"NO";
}