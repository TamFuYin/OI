#include<bits/stdc++.h>
int main(){
    int a[3];
    std::cin>>a[0]>>a[1]>>a[2];
    std::sort(a,a+3,std::greater<int>());
    std::cout<<a[0]<<a[1]<<a[2];
}