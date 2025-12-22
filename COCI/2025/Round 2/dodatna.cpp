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
    int n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> times(n);
    for(int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        times[i] = {l, r};
    }
    sort(all(times));
    priority_queue<ll> q;
    ll best = 0;
    for(auto [s, e] : times) {
        q.push(-e);
        while(sz(q) > k)
            q.pop();
        while(!q.empty() && -q.top() <= s)
            q.pop();
        if(sz(q) == k)
            best = max(best, -q.top()-s);
    }
    cout << best << "\n";
}