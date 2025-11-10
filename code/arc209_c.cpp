#include<bits/stdc++.h>
const int N=1e5+10;
int s[N],p[N];
int main(){
    int n,x,q;scanf("%d%d%d",&n,&x,&q);
    int l=1,r=n,ans=0;
    for(int i=1;i<=n;i++) scanf("%d",s+i);
    for(int i=1;i<=n;i++) scanf("%d",p+i),ans+=p[i];
    for(int i=n-1;i>=1;i--){
        if(p[i+1]==1) l=(s[i+1]+r-1)/r,r=x;
        else r=(s[i+1]+l-1)/l-1,l=1;
        if(l>r) --ans,l=1,r=x;
    }
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
    }
    printf("%d",ans);
}