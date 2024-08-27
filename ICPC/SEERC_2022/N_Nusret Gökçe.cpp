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
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	vector<int> ans(n, -1);
	priority_queue<pair<int, int>> q;
	for(int i = 0; i < n; i++) {
		q.push({nums[i], i});
	}
	while(!q.empty()) {
		auto curr = q.top();
		q.pop();
		if(ans[curr.second] != -1)
			continue;
		ans[curr.second] = curr.first;
		if(curr.second > 0 && ans[curr.second-1] == -1)
			q.push({curr.first-m, curr.second-1});
		if(curr.second < n-1 && ans[curr.second+1] == -1)
			q.push({curr.first-m, curr.second+1});
	}
	for(int i : ans)
		cout << i << " ";
	cout << "\n";
}