#include<bits/stdc++.h>
const int N=1e5;
char s[N];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int k;
        scanf("%s%d",s,k);
        int n=strlen(s),top=0;
        k=n-k;
        for(int i=0;i<n;i++){
            top+=s[i]=='('?1:-1;
            if(top<0) break;
        }
        if(top<0) {puts("First");continue;}
        int sentou=0,matsubi=0;
        for(int i=0;s[i]=='(';i++) ++sentou;
        for(int i=n-1;s[i]==')';i--) ++matsubi;
        if(k<=2*std::min(sentou,matsubi))
            puts(k&1?"First":"Second");
    }
}