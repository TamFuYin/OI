#include<bits/stdc++.h>
const int N=1e5+10;
using ll=long long;
std::pair<int,int> a[N];
ll s[N];
bool b[N];
std::vector<int> ans;
double eps=1e-7;
int main(){
    // freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i].first),a[i].second=i;
        std::sort(a+1,a+n+1);
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i].first;
        int p,q;scanf("%d%d",&p,&q);
        double K=1.*p/q;
        std::fill(b+1,b+n+1,1);
        int mx=0;
        for(int l=1;l<=n;l++){
            for(int r=l;r<=n;r++){
                if(a[r].first<=(s[r]-s[l-1])*K/(r-l+1)+eps)
                    mx=std::max(mx,r-l+1);
            }
        }
        for(int l=1;l<=n-mx+1;l++){
            int r=l+mx-1;
            if(a[r].first<=(s[r]-s[l-1])*K/(r-l+1)+eps)
                std::fill(b+l,b+r+1,0);
        }
        ans.clear();
        for(int i=1;i<=n;i++) if(b[i]) ans.push_back(a[i].second);
        printf("%d\n",(int)ans.size());
        std::sort(ans.begin(),ans.end());
        for(int i:ans) printf("%d ",i);
        printf("\n");
    }
    return 0;
}