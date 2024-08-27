#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
    int n, m;
    cin >> n >> m;

    int zeros = 0;
    vector<int> books;

    rep(i, 0, n) {
        int x;
        cin >> x;
        if (x == 0) {
            zeros++;
        } else {
            books.push_back(x);
        }
    }
    
    if (zeros > m) {
        cout << "Impossible\n";
        return;
    }

    m -= zeros;
    n = sz(books);

    if (m == n) {
        cout << "Richman\n";
        return;
    }

    auto best_pick = accumulate(books.begin(), books.begin() + m, 0LL);
    auto min_rest = *min_element(books.begin() + m, books.end());

    cout << best_pick + min_rest - 1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}