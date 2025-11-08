#include<cstdio>
char s[1010];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        int i=14;
        while(s[i]!='\"') putchar(s[i++]);
        puts("");
    }
}
