//感觉没什么用啊
#include<bits/stdc++.h>
namespace st{
    void insert(int c){
        int cur=size++;
    }
    void build(char s[]){
        int n=strlen(s);
        for(int i=n-1;i>=0;i--){
            insert(s[i]-'a');
        }
    }
}
char s[N];
int main(){
    scanf("%s",s);
    st::build(s);
}