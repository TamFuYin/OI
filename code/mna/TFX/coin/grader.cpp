#include <bits/stdc++.h>
#include "coin.h"
static int n, x, y, c, T; 
static int vis[105];
int Ask(std::vector<int> a) {
    std::cout << "? "; 
    for(auto id : a) {
        std::cout << id << ' '; 
    }
    std::cout << std::endl;
    int sum = 0; 
    for(auto id : a) {
        if(id < 1 || id > n || vis[id]) {
			std::cout << "invalid query! ><" << std::endl; 
        	exit(0);
        }
        vis[id] = 1; 
        sum += (id == c ? y : x); 
    }
    for(auto id : a) {
        vis[id] = 0;
    }
    std::cout << sum << std::endl; 
    return sum; 
    
}

int main() {
    std::cin >> n >> T;
	
	while(T--) {
		std::cin >> x >> y >> c; 
		int ans = Solve(n); 
	    std::cout << "! " << ans << std::endl; 
	    if(ans == c) {}
	    else std::cout << "Your answer is wrong! ><" << std::endl, exit(0); 
	}
	
	std::cout << "Your answer is correct! :D" << std::endl; 
    return 0; 
}