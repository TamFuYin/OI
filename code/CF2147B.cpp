#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
void solve() {
    freopen(".out","w",stdout);
    int n;cin >> n;
    vector<int> ans(2 * n);
    ordered_set available_slots;
    for (int i = 1; i <= 2 * n; ++i)
        available_slots.insert(i);
    for (int x = n; x >= 1; --x) {
        unordered_map<int, int> remainders;
        for (int k = 0; k <= x; ++k) {
            int p = *available_slots.find_by_order(k);
            int r = p % x;
            if (remainders.count(r)) {
                int q = remainders[r];
                ans[p - 1] = x;
                ans[q - 1] = x;
                available_slots.erase(p);
                available_slots.erase(q);
                break; 
            } else remainders[r] = p;
        }
    }
    for (int i = 0; i < 2 * n; ++i) 
        cout << ans[i] << (i == 2 * n - 1 ? "" : " ");
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin >> t;
    while (t--) solve();
    return 0;
}