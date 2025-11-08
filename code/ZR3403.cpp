#include<bits/stdc++.h>
const int N=2e5+10;
const int lgN=20;
namespace SA{
    int sa[N],rk[N],h[N];
    int st[N][lgN];
    int cnt[N],sa2[N],ork[N];
    void build(char s[],int n){
        int m=256;
        std::fill(ork+1,ork+n*2+1,0);
        std::fill(cnt+1,cnt+m+1,0);
        for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]+1];
        for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
        for(int k=1;k<=n;k*=2){
            int t=0;
            for(int i=n-k+1;i<=n;i++) sa2[++t]=i;
            for(int i=1;i<=n;i++) if(sa[i]-k>=1) sa2[++t]=sa[i]-k;
            std::fill(cnt+1,cnt+m+1,0);
            for(int i=1;i<=n;i++) ++cnt[rk[i]];
            for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) sa[cnt[rk[sa2[i]]]--]=sa2[i];
            std::copy(rk+1,rk+n+1,ork+1);
            m=rk[sa[1]]=1;
            for(int i=2;i<=n;i++)
                rk[sa[i]]=(ork[sa[i]]==ork[sa[i-1]]&&ork[sa[i]+k]==ork[sa[i-1]+k])?m:++m;
        }
        for(int i=1,j=0;i<=n;i++){
            if(rk[i]==1) {h[1]=j=0;continue;}
            if(j) --j;
            while(s[i+j]==s[sa[rk[i]-1]+j]) ++j;
            h[rk[i]]=j;
        }
        for(int i=1;i<=n;i++) st[i][0]=h[i];
        for(int j=0;(1<<j+1)<=n;j++)
            for(int i=1;i+(1<<j+1)-1<=n;i++)
                st[i][j+1]=std::min(st[i][j],st[i+(1<<j)][j]);
    }
    int getmin(int l,int r){
        assert(l<=r);
        int k=31-__builtin_clz(r-l+1);
        return std::min(st[l][k],st[r-(1<<k)+1][k]);
    }
    int LCP(int i,int j){
        return getmin(std::min(rk[i],rk[j])+1,std::max(rk[i],rk[j]));
    }
}
#define ALL(x) x.begin(),x.end()
char s[N];
int ans;
void solve(int n){
    s[n+1]='#';
    for(int i=1;i<=n;i++) s[2*n+2-i]=s[i];
    s[0]=s[2*n+2]=0;
    SA::build(s,n*2+1);
    auto LCP=[&](int i,int j){return i<=0||j>n?0:SA::LCP(i,j);};
    auto LCS=[&](int i,int j){return i<=0||j>n?0:SA::LCP(2*n+2-i,2*n+2-j);};
    auto LCSP=[&](int i,int j){return i<=0||j>n?0:SA::LCP(2*n+2-i,j);};
    ans+=n*(n-1)/2;
    for(int len=2;len<=n;len++){
        for(int i=1;i+len<=n;i+=len){
            int lcp=std::min(LCP(i,i+len),len),lcs=std::min(LCS(i,i+len),len);
            if(lcp+lcs-1==len){
                ans-=LCSP(i-lcs,i+len+lcp)+1;// B'AAB
                if(i-lcs) ans-=LCSP(i-lcs-1,i+len+lcp)+1;// B'cAAB
                if(i+len+lcp<=n) ans-=LCSP(i-lcs,i+len+lcp+1)+1;// B'AAcB
            }
            else ans-=std::max(lcp+lcs-1-len+1,0);
            if(len>=2){
                lcp=std::min(lcp,len-1);
                lcs=std::min(lcs,len-1);
                if(lcp+lcs-1==len-1)// B'AcAB
                    ans-=LCSP(i-lcs,i+len+lcp)+1;
                else ans-=std::max(lcp+lcs-1-(len-1)+1,0);
                if(LCP(i+1,i+len+1)>=len-1) ans-=LCSP(i,i+len*2)+1;
            }
        }
    }
}
char t[N];
int main(){
    // freopen("sunzh1.in","r",stdin);
    freopen(".in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        scanf("%s",t+1);
        int n=strlen(t+1);ans=0;
        int las=1;
        for(int i=2;i<=n;i++){
            if(t[i]==t[i-1]) std::copy(t+las,t+i,s+1),solve(i-las),las=i;
            else if(i>2&&t[i]==t[i-2]) std::copy(t+las,t+i,s+1),solve(i-las),las=i-1;
        }
        std::copy(t+las,t+n+1,s+1),solve(n+1-las);
        printf("%d\n",ans);
    }
}