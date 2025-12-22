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
        int n;
        cin >> n;
        ll sum = 0;
        ll best = 0;
        ll gain = 0;
        for(ll i = 1; i <= n; i++) {
            ll a;
            cin >> a;
            sum += a;
            gain = max(gain, -sum+i*i+i+best);
            best = max(best, sum-(i+1)*(i+1)+i+1);
        }
        cout << sum+gain << "\n";
    }
}