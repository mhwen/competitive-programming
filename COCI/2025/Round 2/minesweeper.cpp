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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> bomb(n, vector<int>(m));
    for(int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        r--; c--;
        bomb[r][c]++;
    }
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(bomb[r][c])
                cout << 'B' << " ";
            else {
                int cnt = 0;
                for(int dr = -1; dr <= 1; dr++) {
                    for(int dc = -1; dc <= 1; dc++) {
                        int R = dr+r;
                        int C = dc+c;
                        if(R < 0 || C < 0 || R >= n || C >= m)
                            continue;
                        cnt += bomb[R][C];
                    }
                }
                cout << cnt << " ";
            }
        }
        cout << "\n";
    }
}