const int N=1e5;
struct node{int len,link,next[26];}t[N];int size,last;
void build(){
    last=size=0;
    t[0].len=0;
    t[0].link=-1;
}
void SAM(int c){
    int cur=++size;
    t[cur].len=t[last].len+1;
    int p=last;
    while(p!=-1&&!t[p].next[c]) t[p].next[c]=cur,p=t[p].link;
    if(p==-1) t[cur].link=0;
    else{
        int q=t[p].next[c];
        if(t[p].len+1==t[q].len){
            t[cur].link=q;
        }
        else{
            int clone=++size;
            t[clone].len=t[p].len+1;
            memset(t[clone].next,t[q].next,sizeof(int)*26);
            t[clone].link=t[q].link;
            while(p!=-1&&t[p].next[c]==q)
                t[p].next[c]=clone,
                p=t[p].link;
            t[q].link=clone;
        }
    }
}