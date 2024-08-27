#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;

typedef long long ll;

void solve() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	
	auto questions = (int) count(a.begin(), a.end(), 0);
	
	int l = 0;
	int r = questions;
	pair<int, int> ans = pair{-1, -1};
	
	auto compute = [&](int merges) {
		int cards = questions - merges;
		
		int total_sum = 1;
		int num_components = 1;
		int question_number = 0;
				
		for (auto x : a) {
			if (x == -1 || (x == 0 && question_number >= cards)) {
				if (num_components == 1) {
					return pair{-1, -1};
				} else {
					num_components--;
				}
			} else {
				total_sum++;
				num_components++;
			}
			
			if (x == 0) {
				question_number++;
			}
		}
		
		auto g = gcd(total_sum, num_components);
		return pair{total_sum / g, num_components / g};
	};
	
	while (l <= r) {
		int m = (l + r) / 2;
		auto res = compute(m);
		
		if (res.first != -1) {
			if (ans.first == -1 || (ll) ans.first * res.second <= (ll) res.first * ans.second) {
				l = m + 1;
				ans = res;
			} else {
				r = m - 1;
			}
		} else {
			r = m - 1;
		}
	}
	
	if (ans.first == -1) {
		cout << "-1\n";
	} else {
		cout << ans.first << ' ' << ans.second << '\n';
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