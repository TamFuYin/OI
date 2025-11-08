#include<bits/stdc++.h>
const int N=1e6;
int p[N],q[N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",p+i),q[p[i]]=i;
    bool yes=1;
    for(int i=1;i<n;i++) yes&=std::abs(q[i]-q[i+1])<=2;
    puts(yes?"Yes":"No");
}