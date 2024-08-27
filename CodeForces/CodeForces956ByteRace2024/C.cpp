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

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector vals(3, vector<ll>(n));
		ll tot = 0;
		for(int p = 0; p < 3; p++) {
			for(int i = 0; i < n; i++) {
				cin >> vals[p][i];
				tot += vals[p][i];
			}
		}
		tot /= 3;
		ll needed = (tot+2)/3;
		
		vector<int> order{0, 1, 2};
		
		bool good = false;
		vector<pair<int, int>> ans(3);
		
		auto check = [&]() {
			int index = 0;
			for(int p : order) {
				int start = index;
				ll sum = 0;
				while(index < n && sum < needed) {
					sum += vals[p][index];
					index++;
				}
				if(sum < needed)
					return false;
				ans[p].first = start;
				ans[p].second = index-1;
			}
			return true;
		};
		
		do {
			if(check()) {
				good = true;
				break;
			}
		}
		while(next_permutation(all(order)));
		
		if(!good)
			cout << -1 << "\n";
		else {
			for(auto [l, r] : ans)
				cout << l+1 << " " << r+1 << " ";
			cout << "\n";
		}
	}
}