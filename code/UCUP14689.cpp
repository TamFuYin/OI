#include<bits/stdc++.h>
const int N=2e3+10;
int a[N][N],b[N][N];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            scanf("%d",&a[i][j]);
}
/*
每次剥掉一个叶子，父亲就是使其对于剩下列都异或相同的行。
*/