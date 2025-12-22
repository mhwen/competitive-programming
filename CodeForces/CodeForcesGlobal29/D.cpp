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

pair<int, int> brute(vector<int> nums) {
    int n = sz(nums);
    map<int, int> cnts;
    for(int i = 0; i < n; i++) {
        cnts[nums[i]]++;
    }
    map<map<int, int>, pair<int, int>> a;
    map<map<int, int>, pair<int, int>> b;
    auto dfs = [&](auto&& self, map<int, int> curr, int move) -> pair<int, int> {
        if(move == 0) {
            if(a.count(curr))
                return a[curr];
            pair<int, int> best{0, 0};
            for(auto [v, amt] : curr) {
                map<int, int> cop = curr;
                cop.erase(v);
                if(v-1)
                    cop[v-1] += amt;
                pair<int, int> res = self(self, cop, 1-move);
                res.first += amt;
                best = max(best, res);
            }
            return a[curr] = best;
        }
        else {
            if(b.count(curr))
                return b[curr];
            pair<int, int> best{0, 0};
            for(auto [v, amt] : curr) {
                map<int, int> cop = curr;
                cop.erase(v);
                if(v-1)
                    cop[v-1] += amt;
                pair<int, int> res = self(self, cop, 1-move);
                res.second += amt;
                if(res.second > best.second)
                    best = res;
            }
            return b[curr] = best;
        }
    };
    return dfs(dfs, cnts, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> a(n);
        map<ll, ll> cnts;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            cnts[a[i]]++;
        }
        
        ll A = 0, B = 0;
        vector<ll> odds;
        for(auto [v, amt] : cnts) {
            A += amt*(v/2);
            B += amt*(v/2);
            if(v%2==1)
                odds.pb(amt);
        }
        sort(all(odds));
        reverse(all(odds));
        for(int i = 0; i < sz(odds); i+=2) {
            A += odds[i];
        }
        for(int i = 1; i < sz(odds); i+=2) {
            B += odds[i];
        }
        cout << A << " " << B << "\n";
        // auto [AA, BB] = brute(a);
        // if(A != AA || B != BB) {
            // cout << "BAD=======" << endl;
            // cout << AA << " " << BB << endl;
            // return -1;
        // }
    }
    
}