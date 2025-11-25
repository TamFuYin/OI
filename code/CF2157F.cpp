#include<bits/stdc++.h>
int main(){
    int n;scanf("%d",&n);
    std::vector<std::pair<int,int>> ans;
    for(int r=1;r<(1<<6);r++)
        for(int i=n;i>=1;i--) if((i&(1<<6)-1)==r) ans.emplace_back(i,1);
    for(int r=1;r<(1<<6);r++)
        for(int i=n;i>=1;i--) if((i&(1<<12)-1)==(r<<6)) ans.emplace_back(i,1<<6);
    for(int r=1;r<(1<<6);r++)
        for(int i=n;i>=1;i--) if((i&(1<<18)-1)==(r<<12)) ans.emplace_back(i,1<<12);
    printf("%d\n",(int)ans.size());
    for(auto i:ans) printf("%d %d\n",i.first,i.second);
}