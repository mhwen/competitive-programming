#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int INF = 1e9;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    int n, K;
    cin >> n >> K;
    vector<vector<pair<int, int>>> places(K);
    vector<vector<int>> costs(K);
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            int num;
            cin >> num;
            num--;
            places[num].push_back({r, c});
            costs[num].push_back(INF);
        }
    }
    for(int i = 0; i < sz(places[0]); i++) {
        costs[0][i] = 0;
    }

    auto dist = [&](pair<int, int> a, pair<int, int> b) {
        return abs(a.first-b.first)+abs(a.second-b.second);
    };

    for(int i = 0; i+1 < K; i++) {
        for(int j = 0; j < sz(places[i]); j++) {
            for(int k = 0; k < sz(places[i+1]); k++) {
                costs[i+1][k] = min(costs[i+1][k], costs[i][j]+dist(places[i][j], places[i+1][k]));
            }
        }
    }
    int best = INF;
    for(int i : costs[K-1])
        best = min(best, i);
    if(best == INF) {
        cout << -1 << "\n";
    }
    else {
        cout << best << "\n";
    }
	return 0;
}
