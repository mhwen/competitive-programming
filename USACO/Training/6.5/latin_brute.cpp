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

ll fact(ll n) {
    ll res = 1;
    for(ll i = 1; i <= n; i++)
        res *= i;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> used(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        used[i][i] = true;
    for(int i = 0; i < n; i++)
        used[0][i] = true;
    vector<vector<int>> grid(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++)
        grid[0][i] = i;
    for(int i = 0; i < n; i++)
        grid[i][i] = 0;
    
    ll ans = 0;
    auto go = [&](auto&& self, int curr, int r) {
        if(curr == n) {
            ans++;
            return;
        }
        for(int c = 0; c < n; c++) {
            if(grid[r][c] != -1)
                continue;
            if(used[curr][c])
                continue;
            grid[r][c] = curr;
            used[curr][c] = true;
            if(r == n-1)
                self(self, curr+1, 1);
            else
                self(self, curr, r+1); 
            grid[r][c] = -1;
            used[curr][c] = false; 
        }
    };
    go(go, 1, 1);
    cout << ans*fact(n-1) << "\n";
}