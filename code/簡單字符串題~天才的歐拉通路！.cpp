#include<cstdio>
const int N=21,L=1e5;
int s[N][L];
bool dltd[N];
bool is_sub(char a[],char b[]){
    int lena=strlen(a),lenb=strlen(b);
    for(int i=0;i<lenb;i++){
    }
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%s",s[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
        if(!dltd[j]) dltd[j]=is_sub(s[i],s[j]);
    }
}