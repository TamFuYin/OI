#include<bits/stdc++.h>
const int N=1e5;
int s[N];
int w[N];
int n;
std::mt19937 rnd(time(0));
std::set<int> vis;
int main(){
    int T,k;scanf("%d%d",&T,&k);++k;
    while(T--){
        scanf("%d",&n);
        std::fill(s+1,s+n+1,-1);
        if(k==2){
        	int x=0,a1,a2,a3;
        	vis.clear();
        	while(1){
        		a1=rnd()%k,a2=rnd()%k,a3=rnd()%k;
        		if(vis.find(a1*k*k+a2*k+a3)!=vis.end()) continue;
        		vis.insert(a1*k*k+a2*k+a3);
        		printf("? %d%d%d\n",a1,a2,a3);fflush(stdout);
        		scanf("%d",&x);
        		if(x) break;
        	}
        	int fr=INT_MAX;
        	while(x--){
        		int p;scanf("%d",&p);
        		s[p]=a1,s[p+1]=a2,s[p+2]=a3;
        		fr=std::min(fr,p);
        	}
        	for(int i=fr;i<=n;i++){
        		if(s[i]==-1){
        			for(int l=1;l<k;l++){
	        			printf("? ");
	        			for(int j=fr;j<i;j++) printf("%d",s[j]);
	        			printf("%d\n",l);fflush(stdout);
	        			scanf("%d",&x);
	        			bool yes=0;
	        			while(x--){
	        				int p;scanf("%d",&p);
	        				if(p!=fr) continue;
	        				yes=1;
	        			}
	        			if(yes){
							s[i]=l;
							break;
						}
        			}
        			if(s[i]==-1) s[i]=0;
        		}
        	}
        	for(int i=fr-1;i>=1;i--){
        		for(int l=1;l<k;l++){
        			printf("? %d",l);
        			for(int j=i+1;j<=n;j++) printf("%d",s[j]);
        			puts("");fflush(stdout);
        			scanf("%d",&x);
        			bool yes=0;
        			while(x--){
        				int p;scanf("%d",&p);
        				if(p!=i) continue;
        				yes=1;
        			}
        			if(yes){
        				s[i]=l;
        				break;
        			}
        		}
        		if(s[i]==-1) s[i]=0;
        	}
            printf("! ");for(int i=1;i<=n;i++) printf("%d",s[i]);
            puts("");fflush(stdout);
        }
        else{
        	int x=0,a1,a2;
        	vis.clear();
        	while(1){
        		a1=rnd()%k,a2=rnd()%k;
        		if(vis.find(a1*k+a2)!=vis.end()) continue;
        		vis.insert(a1*k+a2);
        		printf("? %d%d\n",a1,a2);fflush(stdout);
        		scanf("%d",&x);
        		if(x) break;
        	}
        	int fr=INT_MAX;
        	while(x--){
        		int p;scanf("%d",&p);
        		s[p]=a1,s[p+1]=a2;
        		fr=std::min(fr,p);
        	}
        	for(int i=fr;i<=n;i++){
        		if(s[i]==-1){
        			for(int l=1;l<k;l++){
	        			printf("? ");
	        			for(int j=fr;j<i;j++) printf("%d",s[j]);
	        			printf("%d\n",l);fflush(stdout);
	        			scanf("%d",&x);
	        			bool yes=0;
	        			while(x--){
	        				int p;scanf("%d",&p);
	        				if(p!=fr) continue;
	        				yes=1;
	        			}
	        			if(yes){
							s[i]=l;
							break;
						}
        			}
        			if(s[i]==-1) s[i]=0;
        		}
        	}
        	for(int i=fr-1;i>=1;i--){
        		for(int l=1;l<k;l++){
        			printf("? %d",l);
        			for(int j=i+1;j<=n;j++) printf("%d",s[j]);
        			puts("");fflush(stdout);
        			scanf("%d",&x);
        			bool yes=0;
        			while(x--){
        				int p;scanf("%d",&p);
        				if(p!=i) continue;
        				yes=1;
        			}
        			if(yes){
        				s[i]=l;
        				break;
        			}
        		}
        		if(s[i]==-1) s[i]=0;
        	}
            printf("! ");for(int i=1;i<=n;i++) printf("%d",s[i]);
            puts("");fflush(stdout);
		}
    }
}