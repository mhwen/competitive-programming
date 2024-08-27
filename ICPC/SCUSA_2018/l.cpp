#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using ll = long long;
using namespace std;

ll cb(ll x) {
    return x * x * x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    // {gravity, is_human}
    vector<pair<ll, bool>> planets(n);
    for (int i = 0; i < n; i++) {
        int gg;
        char t;
        cin >> gg >> t;
        planets[i] = {gg, t == 'h'};
    }

    vector<set<int>> adj_to(n);

    int m;
    cin >> m;

    set<pair<int, int>> adj;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (x > y) swap(x, y);
        adj.insert({x, y});
        
        adj_to[x].insert(y);
        adj_to[y].insert(x);
    }

    auto has_common = [&](int x, int y) {
        auto &adj1 = adj_to[x];
        auto &adj2 = adj_to[y];

        for (auto a : adj1) {
            if (adj2.count(a)) {
                return true;
            }
        }

        return false;
    };

    auto has_not_common = [&](int x, int y) {
        auto &adj1 = adj_to[x];
        auto &adj2 = adj_to[y];

        for (auto a : adj1) {
            if (a != y && !adj2.count(a)) {
                return true;
            }
        }

        return false;
    };

    vector<pair<ll, int>> humans;
    vector<pair<ll, int>> aliens;

    for (int i = 0; i < n; i++) {
        if (planets[i].second) {
            humans.push_back({planets[i].first, i});
        } else {
            aliens.push_back({planets[i].first, i});
        }
    }

    sort(humans.begin(), humans.end());
    sort(aliens.begin(), aliens.end());

    ll ans = 4e18;
    auto check = [&](int i, int j) {
        // know i is human, j is not
        ll cost1 = abs(cb(planets[i].first) - cb(planets[j].first));

        bool is_adj = adj.count(minmax(i, j));
        
        ll cost2, cost3;
        if (is_adj) {
            cost2 = abs(cb(planets[i].first - 1) - cb(planets[j].first + 1));
            cost3 = abs(cb(planets[i].first + 1) - cb(planets[j].first - 1));
        } else {
            cost2 = abs(cb(planets[i].first - 1) - cb(planets[j].first));
            cost3 = abs(cb(planets[i].first) - cb(planets[j].first - 1));
        }

        ans = min({ans, cost1, cost2, cost3});

        int x = i;
        int y = j;

        // some other stuff
        if (has_common(x, y)) {
            ans = min(ans, abs(cb(planets[i].first + 1) - cb(planets[j].first + 1)));
        }

        if (has_not_common(x, y)) {
            ans = min(ans, abs(cb(planets[i].first + 1) - cb(planets[j].first)));
        }

        if (has_not_common(y, x)) {
            ans = min(ans, abs(cb(planets[i].first) - cb(planets[j].first + 1)));
        }
    };

    for (auto [hg, i] : humans) {
        auto it = lower_bound(aliens.begin(), aliens.end(), pair{hg, 0});
        int cnt = 0;

        auto cur = it;
        while (cnt < 5 && cur != aliens.end()) {
            auto j = cur->second;
            check(i, j);
            cur++;
            cnt++;
        }

        cur = it;
        cnt = 0;
        while (cnt < 5 && cur != aliens.begin()) {
            cur--;
            auto j = cur->second;
            check(i, j);
            cnt++;
        }
    }

    cout << ans << '\n';

    return 0;
}