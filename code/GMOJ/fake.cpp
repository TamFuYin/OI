#include<bits/stdc++.h>
const int N=5e3+10;
int ls[N],to[N*N],nx[N*N],tot;
char e[N][N],tmp[N];
int s[N];
std::vector<int> p[N];
int from[N],c,n;
std::vector<int> scc[N];
void add(int u,int v){
    nx[++tot]=ls[u];
    to[ls[u]=tot]=v;
}
int low[N],dfn[N],DFN;
int stack[N],top;
bool instack[N];
void dfs(int u){
    instack[stack[++top]=u]=1;
    low[u]=dfn[u]=++DFN;
    for(int i=ls[u];i;i=nx[i]){
        int v=to[i];
        if(!dfn[v]){
            dfs(v);
            low[u]=std::min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=std::min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        ++c;
        do{
            scc[c].push_back(stack[top]);
            from[stack[top]]=c;
            instack[stack[top]]=0;
        }while(stack[top--]!=u);
    }
}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
bool fc[N],old_fc[N];
int f[N],r[N];
int binom[N][N];
const int MOD=1e9+7;
int main(){
    freopen("fake.in","r",stdin);
    // freopen("fake.out","w",stdout);
    int a,b;scanf("%d%d%d",&n,&a,&b);
    for(int i=0;i<=n;i++){
        binom[i][0]=binom[i][i]=1;
        for(int j=1;j<i;j++){
            binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%s",e[i]+1);
        for(int j=1;j<=n;j++)
            if(e[i][j]=='1')
                add(i,j);//,printf("%d %d\n",i,j);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    for(int i=1;i<=n;i++){
        scanf("%d%s",&s[i],tmp+1);
        for(int j=1;j<=s[i];j++){
            if(tmp[j]=='1')
            p[i].push_back(j);
        }
        r[i]=p[i].size();
    }
    for(int i=c,d=0;i>=1;i--){
        int old_d=d;
        for(int u:scc[i]){
            printf("%d ",u);
            if(!d) d=s[u];
            else d=gcd(d,s[u]);
        }
        memcpy(old_fc,fc,sizeof fc);
        memset(fc,0,sizeof fc);
        for(int j=0;j<old_d;j++){
            if(old_fc[j]){
                fc[j%d]=1;
            }
        }
        for(int u:scc[i]){
            for(int t:p[u])
                fc[t%d]=1;
        }
        int sum=0;
        for(int j=0;j<d;j++) sum+=fc[j];
        printf(":%d %d\n",d,sum);
        for(int u:scc[i]){
            f[u]=s[u]/d*sum;
        }
    }
    int ans=0;
    for(int u=1;u<=n;u++){
    	printf("%d %d\n",r[u],f[u]);
        int cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            if(r[i]>f[u]||r[i]==f[u]&&i<u) ++cnt1;
            else if(f[i]>f[u]||f[i]==f[u]&&i<u) ++cnt2;
        }
        // printf("%d %d %d\n",f[u],cnt1,cnt2);
        if(cnt1<a){
	        for(int x=std::max(0,std::max(b-1+cnt1-a,b-cnt2-1));x<=cnt1&&x<=b-1;x++){
	            (ans+=1ll*binom[cnt1][x]*binom[cnt2][b-x-1]%MOD)%=MOD;
	            // printf("%d\n",binom[cnt2][x]*binom[cnt1][b-1-x]);
	        }
    	}
    }
    printf("%d",ans);
}
