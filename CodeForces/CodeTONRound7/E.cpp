#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
 
int query(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n;
	r += n;
	int ans = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			ans += tree[l];
			l++;
		}
		if(r%2==0) {
			ans += tree[r];
			r--;
		}
	}
	return ans;
}
 
void update(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	while(pos > 0) {
		tree[pos] += val;
		pos >>= 1;
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		
	int n;
	cin >> n;
	vector<int> nums(n);
	vector<pair<int, int>> segments;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		nums[i]--;
		if(nums[i] < i) {
			segments.push_back({i, nums[i]+n});
		}
		else {
			segments.push_back({i, nums[i]});
		}
	}
	
	for(int i = 0; i < n; i++) {
		if(nums[i] >= i) {
			segments.push_back({i+n, nums[i]+n});
		}
	}
	
	vector<int> starts((int)segments.size());
	vector<int> ends((int)segments.size());
	for(int i = 0; i < (int)segments.size(); i++) {
		starts[i] = segments[i].first;
		ends[i] = segments[i].second;
	}

	vector<vector<int>> startEvents(2*n);
	vector<vector<int>> endEvents(2*n);
	for(int i = 0; i < (int)segments.size(); i++) {
		startEvents[starts[i]].push_back(i);
		endEvents[ends[i]].push_back(i);
	}
	vector<int> active(n*4);
	vector<int> ended(n*4);
	vector<int> contains((int)segments.size());
	vector<int> contained((int)segments.size());
	for(int i = 0; i < 2*n; i++) {
		update(i, (int)startEvents[i].size(), active);
		for(int id : endEvents[i]) {
			update(starts[id], 1, ended);
		}
		
		for(int id : endEvents[i]) {
			contains[id] = query(starts[id], i, ended)-1;
			contained[id] = query(0, starts[id], active)-1;
		}
		
		for(int id : endEvents[i]) {
			update(starts[id], -1, active);
		}
	}
	
	vector<int> ans(n);
	
	for(int i = 0; i < n; i++) {
		ans[nums[i]] = segments[i].second-segments[i].first-contains[i];
	}
	
	for(int i : ans)
		cout << i << " ";
	cout << "\n";
	}
}