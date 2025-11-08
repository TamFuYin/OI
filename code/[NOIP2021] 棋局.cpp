#include<bits/stdc++.h>
#include<bits/extc++.h>
const int N=1e6;
int n,m,e,q;
int mp(int x,int y){return (x-1)*m+y;}
int c[N];
const int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
int d[N][4];
using set=__gnu_pbds::tree<std::pair<int,int>,__gnu_pbds::null_type,std::less<std::pair<int,int> >,
__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
void combine(set& a,const set& b){
	
}
bool vis[N];
int par[N],siz[N],rt[N][3];
int findp(int x){
	if(par[x]==x) return x;
	return par[x]=findp(par[x]);
}
void print(int p){
	if(!p) return;
	printf("%d(%d,->%d,->%d)\n",p,sum[p],ls[p],rs[p]);
	print(ls[p]);print(rs[p]);
}
void merge(int x,int y){
	x=findp(x),y=findp(y);
	if(x==y) return;
	if(siz[x]<siz[y]) std::swap(x,y);
	par[y]=x;siz[x]+=siz[y];
	for(int i=0;i<2;i++)
		combine(t[x][i],t[y][i],1,q);
	combine(t[x][2],t[y][2],1,n*m);
}
set t[N];
void merge_p(int x,int y){
	for(int i=0,lst=0,te;i<4;i++){
		if(c[te=d[mp(x,y)][i]]==3){
			if(!lst) lst=te;
			else merge(lst,te);
		}
	}
	if(c[d[mp(x,y)][0]]==c[d[mp(x,y)][1]]&&c[d[mp(x,y)][0]]==2){
		merge(d[mp(x,y)][0],d[mp(x,y)][1]);
	}
	if(c[d[mp(x,y)][2]]==c[d[mp(x,y)][3]]&&c[d[mp(x,y)][2]]==2){
		merge(d[mp(x,y)][2],d[mp(x,y)][3]);
	}
	for(int i=0,te;i<4;i++){
		if(c[te=d[mp(x,y)][i]]&&!vis[findp(te)]){
			vis[findp(te)]=1;
			if(te==1) printf("INS %d,%d\n",x,y),print(rt[1][2]),printf("->\n");
			insert(rt[findp(te)][2],mp(x,y),1,n*m);
			if(te==1) print(rt[1][2]);
		}
	}
	for(int i=0,te;i<4;i++)
		if(c[te=d[mp(x,y)][i]]) vis[findp(te)]=0;
}
void insert_p(int x,int y,bool col,int lv){
	for(int i=0,te;i<4;i++){
		if(c[te=d[mp(x,y)][i]]){
			insert(rt[findp(te)][col],lv,1,q);
		}
	}
}
void erase_p(int x,int y,bool col,int lv){
	for(int i=0,te;i<4;i++){
		if(c[te=d[mp(x,y)][i]]){
			erase(rt[findp(te)][col],lv,1,q);
		}
	}
}
int solve(int x,int y,bool col,int lv){
	int cc=0,c0=0;
	for(int i=0,te;i<4;i++)
		if(c[te=d[mp(x,y)][i]]){
			if(!vis[findp(te)]){
				vis[findp(te)]=1;
				combine(cc,rt[findp(te)][col],1,q);
//				combine(c0,rt[findp(te)][2],1,n*m);
			}
		}
	for(int i=0,te;i<4;i++)
		if(c[te=d[mp(x,y)][i]]) vis[findp(te)]=0;
	printf("%d %d\n",query(cc,lv,1,q),sum[c0]);
	return query(cc,lv,1,q)+sum[c0];
}
int ans[N];
char s[N];
int clv[N],bset[N];
struct operate{int col,lv,x,y;}o[N];
int main(){
	freopen("input","r",stdin);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);e=TS=0;
		memset(d+1,0,sizeof(int)*n*m*4);
		for(int i=1;i<=n;i++){
			scanf("%s",s+1);
			for(int j=1;j<m;j++)
				c[d[mp(i,j)][1]=d[mp(i,j+1)][0]=++e]=s[j]-'0';
		}
		for(int i=1;i<n;i++){
			scanf("%s",s+1);
			for(int j=1;j<=m;j++)
				c[d[mp(i,j)][3]=d[mp(i+1,j)][2]=++e]=s[j]-'0';
		}
		std::iota(par+1,par+e+1,1);
		std::fill(siz+1,siz+e+1,1);
		std::fill(clv+1,clv+q+1,0);
		memset(rt+1,0,sizeof(int)*3*e);
		std::fill(bset+1,bset+n*m+1,0);
		for(int i=1;i<=q;i++)
			scanf("%d%d%d%d",&o[i].col,&o[i].lv,&o[i].x,&o[i].y),++clv[o[i].lv];
		for(int i=1;i<=q;i++) clv[i]+=clv[i-1];
		for(int i=q;i>=1;i--) o[i].lv=clv[o[i].lv]--;
		for(int i=1;i<=q;i++) insert_p(o[i].x,o[i].y,o[i].col,o[i].lv),bset[mp(o[i].x,o[i].y)]=1;
		for(int x=1;x<=n;x++) for(int y=1;y<=m;y++) if(!bset[mp(x,y)]) merge_p(x,y);
		for(int i=q;i>=1;i--){
			erase_p(o[i].x,o[i].y,o[i].col,o[i].lv);
			merge_p(o[i].x,o[i].y);
			ans[i]=solve(o[i].x,o[i].y,o[i].col^1,o[i].lv)-1;
		}
		for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	}
}
