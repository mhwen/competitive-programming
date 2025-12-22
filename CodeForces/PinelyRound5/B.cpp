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
        vector<string> grid(n);
        for(int r = 0; r < n; r++)
            cin >> grid[r];
        int cnt = 0;
        
        auto get = [&](int r, int c) {
            if(r < 0 || c < 0 || r >= n || c >= n)
                return 0;
            if(grid[r][c] == '#')
                return 1;
            return 0;
        };
        
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                cnt += get(r, c);
            }
        }
        bool good = false;
        if(cnt == 0)
            good = true;
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                if(get(r,c)+get(r+1,c)+get(r,c+1)+get(r+1,c+1) == cnt) {
                    good = true;
                }
            }
        }
        map<int, int> upleft;
        map<int, int> downright;
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                upleft[r+c]+=get(r,c);
                downright[r-c]+=get(r,c);
            }
        }
        for(auto [v, amt] : upleft) {
            if(upleft.count(v+1) && amt+upleft[v+1] == cnt)
                good = true;
        }
        for(auto [v, amt] : downright) {
            if(downright.count(v+1) && amt+downright[v+1] == cnt)
                good = true;
        }
        if(good)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}