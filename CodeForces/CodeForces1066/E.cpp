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
        int n, k;
        cin >> n >> k;
        vector<int> cnts(4*n+5);
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            cnts[a]++;
        }
        stack<pair<int, int>> s;
        int ans = 0;
        for(int i = sz(cnts)-1; i >= 0; i--) {
            int amt = cnts[i];
            int last = i;
            while(amt > k) {
                auto [id, a] = s.top();
                s.pop();
                amt += a-1;
                last = id;
            }
            ans = max(ans, last-i);
            s.push({last, amt});
        }
        cout << ans << "\n";
    }
}