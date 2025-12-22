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
        vector grid(n+1, vector<ll>(n+1));
        for(int r = 1; r <= n; r++) {
            for(int c = 1; c <= n; c++) {
                cin >> grid[r][c];
                grid[r][c] += grid[r-1][c]+grid[r][c-1]-grid[r-1][c-1];
            }
        }
        int root = 2*(int)sqrt(sqrt(k));
        ll best = 0;
        for(int r1 = 1; r1 < root+5; r1++) {
            for(int r2 = n; r2 >= n-(root+5); r2--) {
                if(r2 < r1)
                    break;
                for(int c1 = 1; c1 < root+5; c1++) {
                    for(int c2 = n; c2 >= n-(root+5); c2--) {
                        if(c2 < c1)
                            break;
                        ll sum = grid[r2][c2]-grid[r1-1][c2]-grid[r2][c1-1]+grid[r1-1][c1-1];
                        if(sum%k==0)
                            best = max(best, sum);
                    }
                }
            }
        }
        cout << best << "\n";
    }
}