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
#include <bitset>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector b(k, vector<bitset<2000>>(101));
    vector a(n, vector<int>(k));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            cin >> a[i][j];
            b[j][a[i][j]].set(i);
        }
    }
    vector<vector<int>> con(n);
    vector<int> deg(n);
    for(int i = 0; i < n; i++) {
        bitset<2000> res;
        res.set();
        for(int j = 0; j < k; j++) {
            if(a[i][j] != 0) {
                res &= b[j][a[i][j]];
            }
        }
        for(int j = 0; j < n; j++) {
            if(j == i)
                continue;
            if(res.test(j)) {
                con[j].pb(i);
                deg[i]++;
            }
        }
    }
    vector<int> ans(n, 1);
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(deg[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        for(int next : con[curr]) {
            ans[next] = max(ans[next], ans[curr]+1);
            deg[next]--;
            if(deg[next] == 0)
                q.push(next);
        }
    }
    cout << *max_element(all(ans)) << "\n";
    
}