#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr ll LEN = 1e6;

bool intersects(int l1, int r1, int l2, int r2) {
	return (l1 <= l2 && l2 <= r1) || (l1 <= r2 && r2 <= r1);
}

int dfsLeft(int curr, vector<bool>& vis, vector<pair<int, int>>& ranges, vector<int>& height) {
	int left = ranges[curr].first;
	vis[curr] = true;
	for(int next = 0; next < (int)ranges.size(); next++) {
		if(vis[next])
			continue;
		if(height[next] < height[curr] && intersects(ranges[curr].first, ranges[curr].second, ranges[next].first, ranges[next].second)) {
			left = min(left, dfsLeft(next, vis, ranges, height));
		}
	}
	return left;
}

int dfsRight(int curr, vector<bool>& vis, vector<pair<int, int>>& ranges, vector<int>& height) {
	int right = ranges[curr].second;
	vis[curr] = true;
	for(int next = 0; next < (int)ranges.size(); next++) {
		if(vis[next])
			continue;
		if(height[next] < height[curr] && intersects(ranges[curr].first, ranges[curr].second, ranges[next].first, ranges[next].second)) {
			right = max(right, dfsRight(next, vis, ranges, height));
		}
	}
	return right;
}

//O(m^3) solution
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> ranges(m);
	vector<int> rangeHeights(m);
	vector<int> preSum(LEN+5);
	for(int i = 0; i < n; i++) {
		int pos;
		cin >> pos;
		preSum[pos]++;
	}
	for(int i = 0; i < LEN; i++) {
		preSum[i+1] += preSum[i];
	}
	
	for(int i = 0; i < m; i++) {
		int l, r, h;
		cin >> l >> r >> h;
		ranges[i] = {l, r};
		rangeHeights[i] = h;
	}
	vector<bool> vis(m);
	int best = 1;
	for(int i = 0; i < m; i++) {
		fill(vis.begin(), vis.end(), false);
		int left = dfsLeft(i, vis, ranges, rangeHeights);
		fill(vis.begin(), vis.end(), false);
		int right = dfsRight(i, vis, ranges, rangeHeights);
		best = max(best, preSum[right]-preSum[left-1]);
	}
	cout << best << "\n";
}