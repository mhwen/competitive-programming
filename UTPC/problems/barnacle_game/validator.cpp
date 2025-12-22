#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define all(x) begin(x), end(x)

using namespace std;
constexpr int MAX_N = 5000;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();
    vector<vector<int>> con(n);
    set<pair<int, int>> seen;
    for(int i = 0; i < n-1; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        u--; v--;
        con[u].push_back(v);
        con[v].push_back(u);
        ensure(u != v);
        if(u > v)
            swap(u, v);
        ensure(seen.count({u, v}) == 0);
        seen.insert({u, v});
    }
    inf.readEof();

    vector<int> vis(n);
    function<bool(int, int)> dfs = [&](int curr, int prev) {
        vis[curr] = 1;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            if(vis[next])
                return false;
            if(!dfs(next, curr))
                return false;
        }
        return true;
    };

    ensure(dfs(0, -1));
    ensure(accumulate(all(vis), 0) == n);
}