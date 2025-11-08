#include<bits/stdc++.h>
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        int a,max=-1e9,min=1e9;
        for(int i=1;i<=n;i++)
        scanf("%d",&a),max=std::max(max,a),min=std::min(min,a);
        printf("%d\n",max-min);
    }
}