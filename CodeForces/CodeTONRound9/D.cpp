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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<int>> f(1e5+5);
	for(int i = 2; i < sz(f); i++) {
		if(f[i].empty()) {
			for(int j = i; j < sz(f); j+=i)
				f[j].push_back(i);
		}
	}
	vector<int> cnt(sz(f));
	for(int i = 2; i < sz(cnt); i++) {
		int hold = i;
		for(auto fact : f[i]) {
			while(hold%fact==0) {
				hold /= fact;
				cnt[i]++;
			}
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> nums(m);
		for(int i = 0; i < m; i++)
			cin >> nums[i];
		sort(all(nums));
		reverse(all(nums));
		vector<int> ans(n);
		bool bad = false;
		for(int i = 1; i <= n; i++) {
			if(cnt[i] >= sz(nums)) {
				bad = true;
				break;
			}
			ans[i-1] = nums[cnt[i]];
		}
		if(bad)
			cout << -1;
		else
			for(int i : ans)
				cout << i << " ";
		cout << "\n";
	}
}