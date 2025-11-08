#include<bits/stdc++.h>
namespace spl{//spaly
    const int N=1e6;
    int fa[N],son[N][2],siz[N],min[N]={INT_MAX};
    #define ls son[o][0]
    #define rs son[o][1]
    void pushup(int o){
    	siz[o]=siz[ls]+siz[rs]+1;
        min[o]=std::min(std::min(min[ls],min[rs]),o);
    }
    bool type(int o){return o==son[fa[o]][1];}
    void rotate(int o){
    	int f=fa[o];bool k=type(o);
    	if(fa[f]) son[fa[f]][type(f)]=o;
    	fa[o]=fa[f];
        son[f][k]=son[o][k^1];
    	if(son[f][k]) fa[son[f][k]]=f;
    	fa[son[o][k^1]=f]=o;
    	pushup(f),pushup(o);
    }
    void splay(int o){
    	while(fa[o]){
//    		printf("%d %d\n",o,fa[o]);
    		if(fa[fa[o]]) rotate(type(o)==type(fa[o])?fa[o]:o);
    		rotate(o);
    	}
    }
    int findrk(int o,int k){
        assert(siz[o]==siz[ls]+siz[rs]+1);
//    	printf("%d\n",o);
    	if(k<=siz[ls]) return findrk(ls,k);
    	else if(siz[ls]+1==k) return o;
    	return findrk(rs,k-siz[ls]-1);
    }
    typedef std::pair<int,int> pii;
    pii split(int o){
    	splay(o);
    	int p=rs;
    	fa[rs]=0;rs=0;
        pushup(o);
    	return {o,p};
    }
    pii splitrk(int o,int k){
    	return split(findrk(o,k));
    }
    int merge(int x,int y){
    	if(!x) return y;
    	if(!y) return x;
    	splay(x),splay(y);
    	splay(x=findrk(x,siz[x]));
    	son[x][1]=y;fa[y]=x;
        pushup(x);
    	return x;
    }
    void print(int o){
        if(!o) return;
        print(ls);
        printf("%d ",o);
        print(rs);
    }
    std::mt19937 rnd(time(0));
    int insert(int o,int p=0){
        assert(!son[o][0]&&!son[o][1]&&!fa[o]);
    	siz[o]=1;min[o]=o;
    	if(p){
    		splay(p);
	    	p=findrk(p,siz[p]);
	    	son[fa[o]=p][1]=o;
            pushup(p);splay(o);
    	}
    	return o;
    }
    int find(int o){
        while(fa[o]) o=fa[o];//,printf("%d\n",o);
        return o;
    }
    int getmin(int o){
    	splay(o);
    	return min[o];
    }
    bool connect(int x,int y){
        return find(x)==find(y);
    }
    int popshift(int o){// æŠŠ o ç§»è‡³æœ«å°¾
    	auto p=split(o);
    	return merge(p.second,p.first);
	}
    #undef ls
    #undef rs
}
int n;
namespace seg{
	const int N=1e6;
    int t[N*4],tag[N*4];
    void pushup(int o){
        t[o]=std::min(t[o<<1],t[o<<1|1]);
    }
    void push(int o,int v){
        tag[o]+=v;t[o]+=v;
    }
    void pushdown(int o){
        if(tag[o]){
            push(o<<1,tag[o]);
            push(o<<1|1,tag[o]);
            tag[o]=0;
        }
    }
    void build(int* a,int l=0,int r=n,int o=1){
        if(l==r){
            t[o]=a[l];
            return;
        }
        int mid=l+r>>1;
        build(a,l,mid,o<<1);
        build(a,mid+1,r,o<<1|1);
        pushup(o);
    }
    void add(int L,int R,int v,int l=0,int r=n,int o=1){
        if(L<=l&&r<=R) return push(o,v);
        int mid=l+r>>1;pushdown(o);
        if(L<=mid) add(L,R,v,l,mid,o<<1);
        if(mid<R) add(L,R,v,mid+1,r,o<<1|1);
        pushup(o);
    }
}
const int N=1e6;
int c[N],p[N];
int cnt[N],rt[N];
int main(){
    memset(spl::min,0x3f,sizeof spl::min);
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
    std::cin.tie(0),std::ios::sync_with_stdio(0);
	// freopen("perm.out","w",stdout);
    int q;std::cin>>n>>q;
    for(int i=1;i<=n;i++) std::cin>>c[i];
    for(int i=1;i<=n;i++) std::cin>>p[i];
    int cur=n;
    for(int i=1;i<=n;i++) if(!rt[i]){
        --cur;spl::insert(i);rt[i]=i;
//        printf("%d\n",spl::find(i));
        for(int j=p[i];j!=i;j=p[j]) spl::insert(j,i),rt[j]=i;
//        printf(">>> ");spl::print(spl::find(i));puts("");
    }
    c[0]=cur;
    for(int i=1;i<=n;i++){
        if(cnt[rt[i]]++) --cur;
        c[i]+=cur;
    }
    seg::build(c);
//    for(int i=1;i<=n;i++) printf("%d ",c[i]);puts("");
    std::cout<<seg::t[1]<<'\n';
    while(q--){
        int op;std::cin>>op;
        if(op==1){
            int x,y;std::cin>>x>>y;
            if(!spl::connect(x,y)){
                seg::add(0,std::max(spl::getmin(x),spl::getmin(y))-1,1);
                spl::merge(spl::popshift(x),spl::popshift(y));
            }
            else{
                spl::popshift(y);auto p=spl::split(x);
                seg::add(0,std::max(spl::getmin(p.first),spl::getmin(p.second))-1,-1);
            }
        }
        else{
            int l,r,v;std::cin>>l>>r>>v;
            seg::add(l,r,v);
        }
        std::cout<<seg::t[1]<<'\n';
    }
}