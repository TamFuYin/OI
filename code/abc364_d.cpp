#include<bits/stdc++.h>
const int N=1e5+10;
int a[N],b[N];
int main(){
    int n,q;scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    std::sort(a+1,a+n+1);
    while(q--){
        int x,k;scanf("%d%d",&x,&k);
        int left=0,right=2e8;
        while(left<right){
            int mid=left+right>>1;
            if(std::upper_bound(a+1,a+n+1,x+mid)-std::lower_bound(a+1,a+n+1,x-mid)>=k) right=mid;
            else left=mid+1;
        }
        printf("%d\n",left);
    }
}
