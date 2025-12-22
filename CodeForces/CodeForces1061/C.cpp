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
    vector<vector<int>> facts(2e5+1);
    for(int i = 1; i < sz(facts); i++) {
        for(int j = i; j < sz(facts); j+=i)
            facts[j].push_back(i);
    }
    int t;
    cin >> t;
    while(t-->0) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        vector<int> p(n+1);
        vector<int> cnt(n+1);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            int g = a[i]/4;
            for(auto f : facts[a[i]]) {
                if(f > g)
                    cnt[f]++;
            }
            p[g]++;
        }
        for(int i = n-1; i >= 0; i--)
            p[i] += p[i+1];
        
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(p[i]+cnt[i] >= n-k)
                ans = i;
        }
        cout << ans << "\n";

    }
}