// 储存处无

void perm_work(int n){
    for(int i=1;i<=n;i++){
        int bg=perm_get(i),j=bg;
        do j=perm_get(j);while(j!=bg);
    }
}