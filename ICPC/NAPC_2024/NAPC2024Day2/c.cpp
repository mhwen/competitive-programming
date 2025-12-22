#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> v(n);
        for(int i = 0; i < n; i++)
            cin >> v[i];
        vector<int> time(n);
        for(int i = 0; i < n; i++)
            cin >> time[i];
        vector<vector<int>> con(n);
        for(int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            con[a].push_back(b);
            con[b].push_back(a);
        }
        vector<ll> dp(n);
        vector<ll> touch(n);
        function<void(int, int)> dfs = [&](int curr, int prev) {
            for(int next : con[curr]) {
                if(next == prev) {
                    continue;
                }
                dfs(next, curr);
            }
            ll childSum = 0;
            ll bestTake = 0;
            vector<pair<ll, int>> returnable;
            vector<pair<ll, int>> gain;
            for(int next : con[curr]) {
                if(next == prev)
                    continue;
                childSum += dp[next];
                bestTake = max(bestTake, v[next]);
                if(time[next] == 3)
                    returnable.push_back({v[next], next});
                gain.push_back({touch[next]+v[next]-dp[next], next});
            }
            sort(returnable.rbegin(), returnable.rend());
            sort(gain.rbegin(), gain.rend());
            ll bestLeave = 0;
            for(int i = 0; i < min(2, sz(returnable)); i++) {
                for(int j = 0; j < min(2, sz(gain)); j++) {
                    if(returnable[i].second == gain[j].second)
                        continue;
                    // cout << "considering gain " << gain[i].first << " returnable " << returnable[j].first 
                    bestLeave = max(bestLeave, returnable[i].first+gain[j].first);
                }
            }


            ll stay = childSum+bestTake;
            ll leave = childSum+bestLeave;
            // cout << curr << " " << stay << " " << leave << endl;
            // cout << "returnable: " << endl;
            // for(auto i : returnable)
                // cout << i.first << " " << i.second << endl;
            // cout << "gain: " << endl;
            // for(auto i : gain)
                // cout << i.first << " " << i.second << endl;

            touch[curr] = childSum;
            dp[curr] = max(stay, leave);
        };
        dfs(0, -1);
        cout << dp[0]+v[0] << "\n";
    }
}