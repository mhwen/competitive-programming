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
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, q;
        cin >> n >> q;
        map<pii, vector<pair<pii, int>>> con;
        for(int i = 0; i < q; i++) {
            int x1, y1, x2, y2, d;
            cin >> x1 >> y1 >> x2 >> y2 >> d;
            x1--; y1--; x2--; y2--; d%=2;
            pii a{x1, y1};
            pii b{x2, y2};
            con[a].pb({b, d});
            con[b].pb({a, d});
        }
        vector color(n, vector<int>(n, -1));
        bool good = true;
        function<void(pii, int)> dfs = [&](pii curr, int C) {
            auto [r, c] = curr;
            if(color[r][c] != -1) {
                if(color[r][c] != C)
                    good = false;
                return;
            }
            color[r][c] = C;
            for(auto [next, d] : con[curr]) {
                dfs(next, (C+d)%2);
            }
        };
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                if(color[r][c] == -1)
                    dfs({r, c}, 0);
            }
        }
        if(!good) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            for(int r = 0; r < n; r++) {
                for(int c = 0; c < n; c++) {
                    if(color[r][c] == 0) {
                        if((r+c)%2==0)
                            cout << 1 << " ";
                        else
                            cout << 3 << " ";
                    }
                    else {
                        if((r+c)%2==0)
                            cout << 4 << " ";
                        else
                            cout << 2 << " ";
                    }
                    
                }
                cout << "\n";
            }
        }
    }
}