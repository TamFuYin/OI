#include<bits/stdc++.h>
const int N=1e5+10;
int a[N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    std::sort(a+1,a+n+1);
    int s=0;
    for(int i=1;i<=n;i++)
        if(s>=a[i]) ++s;
        else --s;
    printf("%d ",s);
    std::reverse(a+1,a+n+1);
    s=0;
    for(int i=1;i<=n;i++)
        if(s>=a[i]) ++s;
        else --s;
    printf("%d\n",s);
}