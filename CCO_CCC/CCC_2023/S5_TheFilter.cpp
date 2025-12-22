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

void solve(set<ll>& nums, ll N) {
    auto process = [&](ll v) -> pair<ll, ll> {
        v *= 3;
        assert(v/N <= 2);
        return pair{v%N, v/N};
    };
    map<ll, bool> val;
    val[0] = val[N] = true;
    map<ll, int> vis;
    vis[0] = vis[N] = 2;
    auto dfs = [&](auto&& self, ll curr) -> bool {
        if(!nums.count(curr))
            return false;
        if(vis[curr] == 2)
            return val[curr];
        vis[curr] = 1;
        auto [next, digit] = process(curr);
        if(digit == 1) {
            if(next == 0)
                val[curr] = true;
            else
                val[curr] = false;
        }
        else {
            if(vis.count(next) && vis[next] == 1)
                val[curr] = true;
            else
                val[curr] = self(self, next);
        }
        vis[curr] = 2;
        return val[curr];
    };
    for(auto num : nums) {
        if(!vis.count(num))
            dfs(dfs, num);
        if(val[num])
            cout << num << "\n";
    }
}

typedef pair<pair<ll, ll>, pair<ll, ll>> info;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll N;
	cin >> N;
	vector<info> ranges;
	auto count = [&]() {
	    ll amt = 0;
	    for(auto [a, _b] : ranges) {
	        auto [lo, hi] = a;
	        amt += hi-lo+1;
	    }
	    return amt;
	};
	ranges.pb({{0, N}, {0, 1}});
	while(count() > (ll)1e6) {
	    vector<info> newRanges;
	    for(auto [a, b] : ranges) {
	        auto [num, denom] = b;
	        auto [lo, hi] = a;
	        ll loCap = ((num*3+1)*N)/(denom*3);
	        ll hiCap = ((num*3+2)*N+denom*3-1)/(denom*3);
	        if(lo <= loCap)
	            newRanges.pb({{lo, loCap}, {num*3, denom*3}});
	        if(hiCap <= hi)
	            newRanges.pb({{hiCap, hi}, {num*3+2, denom*3}});
	    }
	    swap(ranges, newRanges);
	}
	set<ll> nums;
	for(auto [a, _b] : ranges) {
	    auto [lo, hi] = a;
	    for(ll v = lo; v <= hi; v++)
	        nums.insert(v);
	}
	solve(nums, N);
}