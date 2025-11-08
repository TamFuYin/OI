#include<bits/stdc++.h>
const int N=1e5;
int S,m;
int f[100]
struct node{int next[26],fail;}t[N];int siz=1;
void insert(char s[]){
	int n=strlen(s),p=0;
	for(int i=0;i<n;i++){
		if(!t[p].next[s[i]]) t[p].next[s[i]]=siz++;
		p=t[p].next[s[i]];
	}
}
int q[N];
void build(){
	int head=0,tail=1;
	q[1]=0;
	while(head<tail){
		int u=q[++head];
		for(int i=0;i<S;i++){
			int& v=t[u].next[i];
			if(!v) v=t[t[u].fail].next[i];
			else t[q[++tail]=v].fail=t[t[u].fail].next[i];
		}
	}
}
void DP(){
    for(int i=1;i<n;i++){
        for(int s=0;s<(1<<m);s++){
        }
    }
}
int main(){
}