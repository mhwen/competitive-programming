#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

void fill_ans(int l, int r, vector<int> remaining, int depth, vector<int>& ans) {
	if(l == r) {
		ans[l] = remaining.front();
		return;
	}
	vector<int> left, right;
	for(int i : remaining) {
		if(i&(1<<depth)) {
			left.push_back(i);
		}
		else {
			right.push_back(i);
		}
	}
	fill_ans(l, l+(int)left.size()-1, left, depth+1, ans);
	fill_ans(l+(int)left.size(), r, right, depth+1, ans);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> nums(n);
	iota(nums.begin(), nums.end(), 1);
	vector<int> ans(n);
	fill_ans(0, n-1, nums, 0, ans);

	for(int i : ans)
		cout << i << " ";
	cout << endl;
	// for(int i = 0; i < n; i++) {
		// for(int j = i+2; j < n; j+=2) {
			// if(ans[i]+ans[j] == ans[(i+j)/2]*2) {
				// cout << ans[i] << " " << ans[(i+j)/2] << " " << ans[j] << endl;
			// }
		// }
	// }
	

}