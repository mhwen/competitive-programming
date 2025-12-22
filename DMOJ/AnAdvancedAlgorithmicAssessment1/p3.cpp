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

struct DSU {
    int n;
    vector<int> p;
    DSU(int _n) : n(_n), p(n) {
        iota(all(p), 0);
    }
    int getPar(int a) {
        if(p[a] == a)
            return a;
        return p[a] = getPar(p[a]);
    }  
    bool merge(int a, int b) {
        a = getPar(a);
        b = getPar(b);
        if(a == b)
            return false;
        p[b] = a;
        return true;
    }
};

vector<int> solve1() {
    int n;
    cin >> n;
    vector<vector<int>> active(n+1);
    for(int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        active[h].pb(i);
    }
    vector<bool> on(n+2);
    DSU dsu(n+2);
    int comps = 0;
    vector<int> ans;
    for(int c = n; c >= 1; c--) {
        for(auto node : active[c]) {
            on[node] = true;
            comps++;
            if(on[node-1])
                comps -= dsu.merge(node, node-1);
            if(on[node+1])
                comps -= dsu.merge(node, node+1);
        }
        ans.pb(comps);
    }
    reverse(all(ans));
    return ans;
}

void solve2() {
    int n;
    cin >> n;
    vector<int> c(n+1);
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    int curr = 0;
    vector<int> ans;
    vector<int> free;
    for(int h = n; h >= 1; h--) {
        int delta = c[h]-curr;
        while(delta > 0) {
            if(!ans.empty()) {
                ans.pb(0);
                free.pb(sz(ans)-1);
            }
            ans.pb(h);
            if(sz(ans) > n) {
                cout << -1 << "\n";
                return;
            }
            delta--;
        }
        while(delta < 0) {
            if(free.empty()) {
                cout << -1 << "\n";
                return;
            }
            ans[free.back()] = h;
            free.pop_back();
            delta++;
        }
        curr = c[h];
    }
    while(sz(ans) < n)
        ans.pb(0);
    
    for(int a : ans)
        cout << a << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int type;
    cin >> type;
    if(type == 1) {
        auto ans = solve1();
        for(int a : ans)
            cout << a << " ";
        cout << "\n";
    }
    else
        solve2();
}