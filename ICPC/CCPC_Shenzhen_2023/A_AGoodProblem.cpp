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
	int n;
	cin >> n;
	vector<int> nums(n);
	vector<int> a(n);
	set<int> vals;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		vals.insert(nums[i]);
	}
	vector<int> search;
	for(auto v : vals)
		search.push_back(v);

	vector<pair<int, int>> ans;
	function<void(int, int, int)> dnc = [&](int l, int r, int currVal) {
		// cout << " at " << l << " " << r << endl;
		if(l == r) {
			int target = search[l];
			// cout << currVal << " to " << target << endl;
			for(int i = 0; i < target-currVal; i++) {
				ans.push_back({1, currVal+i});
			}
			return;
		}

		//all numbers from [l, r] start at currVal
		int mid = (l+r)/2;
		int floorVal = search[mid+1];
		int ceilVal = search[r];
		// cout << currVal << " to " << floorVal << endl;
		//increase all [mid+1, r] by 1
		for(int i = 0; i < n; i++) {
			if(nums[i] >= floorVal && nums[i] <= ceilVal)
				ans.push_back({2, i+1});
		}
		//increase [mid+1, r] to floor
		for(int i = 1; i < floorVal-currVal; i++) {
			ans.push_back({1, currVal+i});
		}
		dnc(mid+1, r, floorVal);
		dnc(l, mid, currVal);
	};
	
	dnc(0, (int)search.size()-1, 0);
	
	function<bool()> check = [&]() {
		vector<int> sim(n);
		for(auto op : ans) {
			if(op.first == 1) {
				for(int i = 0; i < n; i++) {
					if(sim[i] == op.second)
						sim[i]++;
				}
			}
			else {
				sim[op.second-1]++;
			}
		}
		// for(int i : sim)
			// cout << i << " ";
		// cout << endl;
		for(int i = 0; i < n; i++) {
			if(sim[i] != nums[i])
				return false;
		}
		return true;
	};
	
	if(!check()) {
		cout << "fail" << endl;
		return -1;
	}
	cout << ans.size() << "\n";
	for(auto p : ans)
		cout << p.first << " " << p.second << "\n";
}