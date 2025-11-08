#include<bits/stdc++.h>
const int N=2e5+5;
int a[N];
std::vector<int> p;
int f[N],g[N],mxc[N];
int main(){
    // freopen64("ex_subseq5.in","r",stdin);
    // freopen64("ex_subseq5.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        p.clear();
        int ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            f[i]=1;
            g[i]=INT_MIN;
            mxc[i]=0;
            auto update=[&](int v,int c){
                if(v>=f[i]) g[i]=f[i],mxc[i]=c,f[i]=v;
                else if(v>g[i]) g[i]=v;
            };
            for(int j:p){
                if(a[j]!=a[i]){
                    if(mxc[j]!=a[i]) update(f[j]+1,a[j]);
                    else update(g[j]+1,a[j]);
                }
            }
            // printf("%d %d %d\n",f[i],g[i],mxc[i]);
            auto it=std::find_if(p.begin(),p.end(),[i](int x){return a[x]==a[i];});
            if(it!=p.end()) p.erase(it);
            p.push_back(i);
            if(p.size()==6) p.erase(p.begin());
            ans=std::max(ans,f[i]);
        }
        printf("%d\n",ans);
    }
}