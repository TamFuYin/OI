#include "hack.h"
#include <vector>

int hack(){
    std::vector<long long> x = {1, 2, 3};
    long long a = collisions(x);
    long long b = collisions({92, 65});

    return 42;
}