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
        int x, y;
        cin >> x >> y;
        if(x < y) {
            cout << 2 << "\n";
        }
        else if(x == y) {
            cout << -1 << "\n";
        }
        else {
            assert(x > y);
            int over = x-y;
            int z = min(over, y);
            if(z-1 > 0)
                cout << 3 << "\n";
            else
                cout << -1 << "\n";
            //y-1 + over+1 over >= y
            //y+1 + over-1 over <= y
        }
    }
}