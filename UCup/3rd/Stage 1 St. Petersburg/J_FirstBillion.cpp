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

constexpr int S = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int a, int b) {
		return nums[a] > nums[b];
	});
	
	bool found = false;
	vector<int> ans;
	function<void(int, int, int)> dfs = [&](int id, int curr, int rem) {
		int needed = S-curr;
		if(rem < needed || needed < 0 || id >= n)
			return;
		if(needed == 0) {
			found = true;
			cout << sz(ans) << " ";
			for(int i : ans)
				cout << i+1 << " ";
			cout << "\n";
			return;
		}
		int val = nums[order[id]];
		
		ans.push_back(order[id]);
		dfs(id+1, curr+val, rem-val);
		ans.pop_back();
		if(found)
			return;
		dfs(id+1, curr, rem-val);
	};
	
	dfs(0, 0, 2e9);
	
	
}