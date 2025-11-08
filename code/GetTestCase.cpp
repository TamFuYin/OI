#include<bits/stdc++.h>
int main(){
    freopen("ex_subseq2.in","r",stdin);
    freopen(".in","w",stdout);
    const int TC=24408;
    int T;scanf("%d",&T);
    puts("1");
    for(int t=1;t<=T;t++){
        int n;scanf("%d",&n);
        if(t==TC) printf("%d\n",n);
        for(int i=1;i<=n;i++){
            int a;scanf("%d",&a);
            if(t==TC) printf("%d ",a);
        }
        if(t==TC) puts("");
    }
}