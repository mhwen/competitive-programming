#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int c, x;
            cin >> c >> x;
            c--;

            nums[c] = x;
        } else {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            cout << abs(nums[a] - nums[b]) << '\n';
        }
    }

    return 0;
}