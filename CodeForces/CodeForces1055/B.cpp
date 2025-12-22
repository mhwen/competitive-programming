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
        ll n, x, y, r, c;
        cin >> n >> x >> y >> r >> c;
        ll xRem;
        if(x < r)
            xRem = r;
        else if(x > r)
            xRem = n-r;
        else
            xRem = 0;
        ll yRem;
        if(y < c)
            yRem = c;
        else if(y > c)
            yRem = n-c;
        else
            yRem = 0;
        cout << max(xRem, yRem) << "\n";
    }
}