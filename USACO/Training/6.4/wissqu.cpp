/*
ID: markhwe1
TASK: wissqu
LANG: C++17
*/

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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ifstream cin("wissqu.in");
    ofstream cout("wissqu.out");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<char> s(16);
    for(int i = 0; i < 16; i++)
        cin >> s[i];
    
    auto pos = [](int v) {
        return pair{v/4, v%4};
    };
    auto id = [](int r, int c) {
        return r*4+c;
    };
    
    // auto print = [&](vector<char>& v) {
        // for(int r = 0; r < 4; r++) {
            // for(int c = 0; c < 4; c++) {
                // cout << v[id(r,c)];
            // }
            // cout << endl;
        // }
        // cout << endl;
    // };
    
    vector<char> v(16);
    vector<int> freq(5);
    
    ll ans = 0;
    vector<pair<char, pair<int, int>>> moves;
    auto count = [&]() {
        vector<vector<int>> con(16);
        vector<int> deg(16);
        for(int i = 0; i < 16; i++) {
            if(v[i] == s[i])
                return;
            auto [r, c] = pos(i);
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; dc++) {
                    if(dr == 0 && dc == 0)
                        continue;
                    int R = r+dr;
                    int C = c+dc;
                    if(R < 0 || R >= 4 || C < 0 || C >= 4)
                        continue;
                    if(s[id(R, C)] == v[i]) {
                        con[id(R, C)].pb(i);
                        deg[i]++;
                    }
                }
            }
        }
        
        vector<int> vis(16);
        bool cycle = false;
        function<void(int)> check = [&](int curr) {
            vis[curr] = 1;
            for(int next : con[curr]) {
                if(vis[next] == 1) {
                    cycle = true;
                    return;
                }
                if(vis[next] == 0) {
                    check(next);
                }
            }
            vis[curr] = 2;
        };
        for(int i = 0; i < 16; i++) {
            if(vis[i] == 0) {
                check(i);
            }
        }
        if(cycle)
            return;
        
        vector<pair<char, pair<int, int>>> path;
        function<void(int)> dfs = [&](int step) {
            if(step == 16) {
                if(moves.empty() || path < moves)
                    moves = path;
                ans++;
                return;
            }
            for(int i = 0; i < 16; i++) {
                if(v[i] != 0 && deg[i] == 0) {
                    char C = v[i];
                    v[i] = 0;
                    for(int next : con[i])
                        deg[next]--;
                    path.pb({C, pos(i)});
                    dfs(step+1);
                    for(int next : con[i])
                        deg[next]++;
                    path.pop_back();
                    v[i] = C;
                }
            }
        };

        dfs(0);
    };
    
    
    auto check = [&](int i) {
        for(int j = 0; j < 5; j++) {
            if(freq[j] > 4)
                return false;
            if(j != 3 && freq[j] > 3)
                return false;
        }
        auto [r, c] = pos(i);
        for(int dr = -1; dr <= 1; dr++) {
            for(int dc = -1; dc <= 1; dc++) {
                if(dr == 0 && dc == 0)
                    continue;
                int R = r+dr;
                int C = c+dc;
                if(R < 0 || R >= 4 || C < 0 || C >= 4)
                    continue;
                if(v[id(R, C)] == v[i])
                    return false;
            }
        }  
        return true;
    };
    
    function<void(int)> go = [&](int i) {
        if(i == 16) {
            count();
            return;
        }
        for(char c = 'A'; c <= 'E'; c++) {
            v[i] = c;
            freq[c-'A']++;
            if(check(i))
                go(i+1);
            freq[c-'A']--;
            v[i] = 0;
        }
    };

    go(0);
    for(auto [ch, rc] : moves) {
        auto [r,c] = rc;
        cout << ch << " " << r+1 << " " << c+1 << "\n";
    }
    cout << ans << "\n";
}