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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> nums(n*m);
	for(int i = 0; i < n*m; i++) {
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end());
	vector<int> left(n*m);
	left[0] = 1;
	for(int i = 1; i < n*m; i++) {
		if(nums[i] == nums[i-1])
			left[i] = left[i-1];
		left[i]++;
	}
	for(int k = 1; k <= n; k++) {
		int sz = k;
		int id = -1;
		vector<int> seq(m);
		for(int i = 0; i < m; i++) {
			int end = id+sz;
			int count = min(sz, left[end]);
			seq[i] = nums[end];
			id += sz;
			sz = count;
		}
		for(int i : seq)
			cout << i << " ";
		cout << "\n";
	}
}