/*
类根号分治
分 k ≤ 3 和 k ≥ 5
*/
#include<bits/stdc++.h>
template<typename _T>
void ckmin(_T& a,_T b){a=std::min(a,b);}
template<typename _T>
void ckmax(_T& a,_T b){a=std::max(a,b);}
const int N=81;
char s[N];
int ans,n;
void solve2(){
	static int f[N][N];
	for(int x=1;x<n;x++){
		for(int i=0;i<x;i++){
			for(int j=x;j<n;j++){
				f[i][j]=0;
				if(i>0) ckmax(f[i][j],f[i-1][j]);
				if(j>x) ckmax(f[i][j],f[i][j-1]);
				if(s[i]==s[j]){
					if(i>0&&j>x) ckmax(f[i][j],f[i-1][j-1]+1);
					else ckmax(f[i][j],1);
				}
			}
			// if(f[x-1][n-1]==28) printf("%d\n",x);
			ckmax(ans,f[x-1][n-1]);
		}
	}
}
void solve3(){
	static int f[N][N][N];
	for(int x=1;x<n;x++){
		for(int y=x+1;y<n;y++){
			for(int i=0;i<x;i++){
				for(int j=x;j<y;j++){
					for(int k=y;k<n;k++){
						f[i][j][k]=0;
						if(i>0) ckmax(f[i][j][k],f[i-1][j][k]);
						if(j>x) ckmax(f[i][j][k],f[i][j-1][k]);
						if(k>y) ckmax(f[i][j][k],f[i][j][k-1]);
						if(s[i]==s[j]&&s[j]==s[k]){
							if(i>0&&j>x&&k>y) ckmax(f[i][j][k],f[i-1][j-1][k-1]+1);
							else ckmax(f[i][j][k],1);
						}
					}
				}
			}
			ckmax(ans,f[x-1][y-1][n-1]);
		}
	}
}
void solve5(){//此时可能的单串很短可以直接枚举，然后用序列自动机判断
	static int to[N][26],last[26];
	std::fill(last,last+26,n);
	std::string seq;
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<26;j++)
			to[i][j]=last[j];
		last[s[i]-'a']=i;
	}
	for(int i=0;i<n;i++){
		for(int S=0;S<(1<<std::min(14,n-i-1));S++){
			seq.clear();
			seq.push_back(s[i]);
			for(int j=0;j<14&&j<n-i-1;j++)
				if(S>>j&1) seq.push_back(s[i+j+1]);
			int x=last[seq[0]-'a'],cnt=0,len=seq.size(),i=0;
			while(x<n) x=to[x][seq[(++i)%=len]-'a'],++cnt;
			if(cnt>=len*2) ckmax(ans,cnt/len*len);//,printf("%s %d\n",seq.c_str(),cnt);
		}
	}
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	solve2();solve3();solve5();
	printf("%d",ans);
}
