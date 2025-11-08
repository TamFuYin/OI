#include<bits/stdc++.h>
template<typename T>
void ckmin(T& a,const T& b){if(b<a) a=b;}
template<typename T>
void ckmax(T& a,const T& b){if(b>a) a=b;}
const int N=2e6+10;
char s[N];
int c[3],maj;
int map[N];
char antimap[3];
int min,max;
int n;
bool check(int l,int r){
    bool ret=*std::max_element(c,c+3)<=(r-l+1+1)/2;
    if(s[l-1]) ret&=c[map[s[l-1]]]<=(r-l+1)/2;
    if(s[r+1]) ret&=c[map[s[r+1]]]<=(r-l+1)/2;
    if(s[l-1]&&s[l-1]==s[r+1]) ret&=c[map[s[l-1]]]<=(r-l)/2;
    return ret;
}
int check(int len){
    int L=std::max(1,max-len+1);
    std::fill(c,c+3,0);
    for(int i=L;i<=L+len-1;i++) ++c[map[s[i]]];
    if(check(L,L+len-1)) return L;
    for(int i=L+1;i<=std::min(n-len+1,min);i++){
        --c[map[s[i-1]]],++c[map[s[i+len-1]]];
        if(check(i,i+len-1)) return i;
    }
    return 0;
}
int main(){
    map['C']=0,map['W']=1,map['P']=2;
    antimap[0]='C',antimap[1]='W',antimap[2]='P';
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%s",&n,s+1);
        s[0]=s[n+1]=0;
        min=INT_MAX,max=INT_MIN;
        std::fill(c,c+3,0);
        for(int i=2;i<=n;i++)
            if(s[i-1]==s[i]) ckmin(min,i),ckmax(max,i-1);
        if(min==INT_MAX){
            puts("Beautiful");
            continue;
        }
        for(int i=1;i<=n;i++) ++c[map[s[i]]];
        if(*std::max_element(c,c+3)>(n+1)/2){
            puts("Impossible");
            continue;
        }
        puts("Possible");
        int left=max-min+1,right=n;
        while(left<right){
            int mid=(left+right)>>1;
            if(check(mid)) right=mid;
            else left=mid+1;
        }
        int l=check(left);
        printf("%d %d\n",l,l+left-1);
        for(int i=1;i<l;i++) putchar(s[i]);
        int j=std::max_element(c,c+3)-c;
        char rc;
        if(s[l-1]==antimap[j]){
            if(j==0) putchar(antimap[c[1]>c[2]?1:2]),--c[c[1]>c[2]?1:2];
            else if(j==1) putchar(antimap[c[0]>c[2]?0:2]),--c[c[0]>c[2]?0:2];
            else putchar(antimap[c[0]>c[1]?0:1]),--c[c[0]>c[1]?0:1];
            {
                int j=std::max_element(c,c+3)-c;
                if(s[l+left]==antimap[j]){
                    if(j==0) rc=antimap[c[1]>c[2]?1:2],--c[c[1]>c[2]?1:2];
                    else if(j==1) rc=antimap[c[0]>c[2]?0:2],--c[c[0]>c[2]?0:2];
                    else rc=antimap[c[0]>c[1]?0:1],--c[c[0]>c[1]?0:1];
                }
                else rc=antimap[j],--c[j];
            }
        }
        else{
            {
                int j=std::max_element(c,c+3)-c;
                if(s[l+left]==antimap[j]){
                    if(j==0) rc=antimap[c[1]>c[2]?1:2],--c[c[1]>c[2]?1:2];
                    else if(j==1) rc=antimap[c[0]>c[2]?0:2],--c[c[0]>c[2]?0:2];
                    else rc=antimap[c[0]>c[1]?0:1],--c[c[0]>c[1]?0:1];
                }
                else rc=antimap[j],--c[j];
            }
            j=std::max_element(c,c+3)-c;
            if(s[l-1]==antimap[j]){
                if(j==0) putchar(antimap[c[1]>c[2]?1:2]),--c[c[1]>c[2]?1:2];
                else if(j==1) putchar(antimap[c[0]>c[2]?0:2]),--c[c[0]>c[2]?0:2];
                else putchar(antimap[c[0]>c[1]?0:1]),--c[c[0]>c[1]?0:1];
            }
            else putchar(antimap[j]),--c[j];
        }
        for(int i=l+1;i<l+left-1;i++){
            j=std::max_element(c,c+3)-c;
            putchar(antimap[j]),--c[j];
        }
        putchar(rc);
        for(int i=l+left;i<=n;i++) putchar(s[i]);
        puts("");
    }
}