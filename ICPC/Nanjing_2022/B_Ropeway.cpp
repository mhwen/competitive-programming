#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

vector<ll> get_dp(const vector<int> &a, const string &s, int k) {
	int n = (int) a.size();
	vector<ll> dp(n + 1);
	
	multiset<ll> poss = {0};
	int left = 0;
	for (int i = 1; i <= n; i++) {
		while (left < i - k) {
			poss.erase(poss.find(dp[left]));
			left++;
		}
		dp[i] = *poss.begin() + a[i - 1];
		
		if (s[i-1] == '0') {
			poss.insert(dp[i]);
		} else {
			poss = {dp[i]};
			left = i;
		}
	}
		
	return dp;
}

void solve() {
	int n, k;
	cin >> n >> k;
	
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	
	string s;
	cin >> s;
	
	// cost for [0, i), uses i-1
	vector<ll> dp_forw = get_dp(a, s, k);
	
	reverse(a.begin(), a.end());
	reverse(s.begin(), s.end());
	
	// cost for [i, n), uses i
	auto dp_back = get_dp(a, s, k);
	
	reverse(a.begin(), a.end());
	reverse(s.begin(), s.end());
	reverse(dp_back.begin(), dp_back.end());
	
	int q;
	cin >> q;
		
	while (q--) {
		int p, v;
		cin >> p >> v;
		p--;
		
		ll ans = INFLL;
		
		auto iter_forw = [&](auto f) -> void {
			for (int i = 0; i < k; i++) {
				if (p - i >= 0) {
					f(p - i);
				}
				
				
				if (p - i > 0 && s[p - i - 1] == '1') break;
			}
		};
		
		auto iter_back = [&](auto f) -> void {
			for (int i = 1; i <= k; i++) {
				if (p + i <= n) {
					f(p + i);
				}
				
				if (p + i < n && s[p + i] == '1') break;
			}
		};
		
		// going through p
		ll cost1 = INFLL;
		iter_forw([&](int idx) {
			cost1 = min(cost1, dp_forw[idx]);
		});
		
		ll cost2 = INFLL;
		iter_back([&](int idx) {
			cost2 = min(cost2, dp_back[idx]);
		});

		
		ans = min(ans, cost1 + cost2 + v);
		
		if (s[p] == '0') {
			// try not going through v
			vector<ll> gap_left = {INFLL};
			gap_left.reserve(k);
			iter_forw([&](int idx) {
				gap_left.push_back(dp_forw[idx]);
			});
			
			vector<ll> gap_right = {INFLL};
			gap_right.reserve(k);
			iter_back([&](int idx) {
				gap_right.push_back(dp_back[idx]);
			});
			
			while ((int) gap_left.size() <= k) gap_left.push_back(INFLL);
			while ((int) gap_right.size() <= k) gap_right.push_back(INFLL);
			
			// construct prefix mins
			for (int i = 1; i < (int) gap_left.size(); i++) {
				gap_left[i] = min(gap_left[i], gap_left[i - 1]);
			}
			
			
			for (int i = 1; i < (int) gap_right.size(); i++) {
				gap_right[i] = min(gap_right[i], gap_right[i - 1]);
			}
			
			// match together
			ll cost3 = INFLL;
			for (int i = 0; i < (int) gap_left.size(); i++) {
				int max_other = k - i;
				cost3 = min(cost3, gap_left[i] + gap_right[max_other]);
			}
			
			ans = min(ans, cost3);
		}
		
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	
	while (t--) {
		solve();
	}
	
	return 0;
}