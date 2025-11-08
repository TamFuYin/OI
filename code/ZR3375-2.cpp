#include<bits/stdc++.h>
using namespace std;
namespace spl{
    const int N=1e6+5;
    int fa[N],son[N][2],siz[N],mn[N];
    #define ls son[o][0]
    #define rs son[o][1]
    void pushup(int o){
        siz[o]=siz[ls]+siz[rs]+1;
        int l=ls?mn[ls]:INT_MAX,r=rs?mn[rs]:INT_MAX;
        mn[o]=min(min(l,r),o);
    }
    bool type(int o){return o==son[fa[o]][1];}
    void rotate(int o){
        int f=fa[o],g=fa[f],k=(o==son[f][1]);
        son[f][k]=son[o][k^1];
        if(son[o][k^1]) fa[son[o][k^1]]=f;
        son[o][k^1]=f;fa[f]=o;
        fa[o]=g;
        if(g){
            if(son[g][0]==f) son[g][0]=o;
            else if(son[g][1]==f) son[g][1]=o;
        }
        pushup(f);pushup(o);
    }
    void splay(int o){
        while(fa[o]){
            int f=fa[o],g=fa[f];
            if(g){
                if((o==son[f][1])==(f==son[g][1])) rotate(f);
                else rotate(o);
            }
            rotate(o);
        }
    }
    int findrk(int o,int k){
        while(o){
            int l=son[o][0],lsiz=l?siz[l]:0;
            if(k<=lsiz) o=l;
            else if(k==lsiz+1) return o;
            else k-=lsiz+1,o=son[o][1];
        }
        return 0;
    }
    typedef pair<int,int> pii;
    pii split(int o){
        splay(o);
        int r=son[o][1];
        if(r) fa[r]=0;
        son[o][1]=0;
        pushup(o);
        return {o,r};
    }
    pii splitrk(int o,int k){
        int node=findrk(o,k);
        if(!node) return {o,0};
        return split(node);
    }
    int merge(int x,int y){
        if(!x) return y;
        if(!y) return x;
        int r=findrk(x,siz[x]);
        splay(r);
        son[r][1]=y;fa[y]=r;
        pushup(r);
        return r;
    }
    int find(int o){
        while(fa[o]) o=fa[o];
        return o;
    }
    int insert(int o,int p=0){
        siz[o]=1;son[o][0]=son[o][1]=fa[o]=0;mn[o]=o;
        if(p){
            splay(p);
            int r=findrk(p,siz[p]);
            splay(r);
            son[r][1]=o;fa[o]=r;
            pushup(r);splay(o);
            return find(o);
        }
        return o;
    }
    int getmin(int o){
        splay(o);
        return mn[o];
    }
    bool connect(int x,int y){
        return find(x)==find(y);
    }
    int popshift(int o){
        auto p=split(o);
        return merge(p.second,p.first);
    }
    #undef ls
    #undef rs
}
int n;
namespace seg{
    const int N=1e6+5;
    int t[N<<2],tag[N<<2];
    void pushup(int o){t[o]=min(t[o<<1],t[o<<1|1]);}
    void push(int o,int v){tag[o]+=v;t[o]+=v;}
    void pushdown(int o){
        if(tag[o]){
            push(o<<1,tag[o]);
            push(o<<1|1,tag[o]);
            tag[o]=0;
        }
    }
    void build(int*a,int l=0,int r=n,int o=1){
        tag[o]=0;
        if(l==r){t[o]=a[l];return;}
        int mid=l+r>>1;
        build(a,l,mid,o<<1);
        build(a,mid+1,r,o<<1|1);
        pushup(o);
    }
    void add(int L,int R,int v,int l=0,int r=n,int o=1){
        if(L>R) return;
        if(L<=l&&r<=R){push(o,v);return;}
        int mid=l+r>>1;
        pushdown(o);
        if(L<=mid) add(L,R,v,l,mid,o<<1);
        if(mid<R) add(L,R,v,mid+1,r,o<<1|1);
        pushup(o);
    }
}
const int N=1e6+5;
int c[N],p[N];
bool vis[N];
int cnt[N];
int main(){
    freopen("04.in","r",stdin);
    freopen("04.ans","w",stdout);
    // freopen("perm.in","r",stdin);
    // freopen("perm.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    if(scanf("%d%d",&n,&q)!=2) return 0;
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<=n;i++){
        spl::fa[i]=spl::son[i][0]=spl::son[i][1]=0;
        spl::siz[i]=0;spl::mn[i]=INT_MAX;
    }
    int cur=n;
    for(int i=1;i<=n;i++) if(!vis[i]){
        vis[i]=1;--cur;
        spl::insert(i);
        for(int j=p[i];j!=i;j=p[j]){
            vis[j]=1;
            spl::insert(j,spl::find(i));
        }
    }
    c[0]=cur;
    for(int i=1;i<=n;i++){
        if(cnt[spl::find(i)]++) --cur;
        c[i]+=cur;
    }
    seg::build(c);
    printf("%d\n",seg::t[1]);
    while(q--){
        int op;scanf("%d",&op);
        if(op==1){
            int x,y;scanf("%d%d",&x,&y);
            if(!spl::connect(x,y)){
                int gx=spl::getmin(x),gy=spl::getmin(y);
                seg::add(0,max(gx,gy),1);
                spl::merge(spl::popshift(x),spl::popshift(y));
            }else{
                spl::popshift(y);
                auto p=spl::split(x);
                int a=p.first,b=p.second;
                int ma=spl::getmin(a),mb=spl::getmin(b);
                seg::add(0,max(ma,mb),-1);
            }
        }else{
            int l,r,v;scanf("%d%d%d",&l,&r,&v);
            seg::add(l,r,v);
        }
        printf("%d\n",seg::t[1]);
    }
    return 0;
}