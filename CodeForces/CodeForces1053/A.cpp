#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        set<int> nums;
        for(int i = 0; i < m; i++) {
            int x;
            cin >> x;
            nums.insert(x);
        }
        int curr = 1;
        for(char c : s) {
            if(c == 'A') {
                curr++;
                nums.insert(curr);
            }
            else {
                curr++;
                while(nums.count(curr))
                    curr++;
                nums.insert(curr);
                while(nums.count(curr))
                    curr++;
            }
        }
        cout << sz(nums) << "\n";
        for(auto v : nums)
            cout << v << " ";
        cout << "\n";
    }
}