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

int query(int l, int r, vector<int>& tree) {
	int n = sz(tree)/2;
	l += n; r += n;
	int res = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			res += tree[l];
			l++;
		}
		if(r%2==0) {
			res += tree[r];
			r--;
		}
	}
	return res;
}

void update(int p, vector<int>& tree, int val) {
	int n = sz(tree)/2;
	p += n;
	while(p > 0) {
		tree[p] += val;
		p >>= 1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, k;
		cin >> n >> m >> k;
		vector<int> nums(n);
		vector<pair<int, int>> order;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			nums[i]--;
			order.push_back({nums[i], i});
		}
		vector<int> target(m);
		vector<bool> del(n, true);
		for(int i = 0; i < m; i++) {
			cin >> target[i];
			target[i]--;
			del[target[i]] = false;
		}

		vector<int> tools(k);
		for(int i = 0; i < k; i++) {
			cin >> tools[i];
		}
		
		if(k < n-m) {
			cout << "NO\n";
			continue;
		}
		
		sort(tools.begin(), tools.end());
		tools.resize(n-m);
		multiset<int> remainingTools;
		for(int i : tools)
			remainingTools.insert(i);
		
		sort(order.rbegin(), order.rend());
		set<int> seen;
		seen.insert(-1);
		seen.insert(n);
		
		vector<int> tree(2*n);
		bool pos = true;
		for(auto[val, index] : order) {
			// cout << "at " << val+1 << " " << index << endl;
			if(del[val]) {
				auto it = seen.lower_bound(index);
				it--;
				int left = *it;
				it = seen.upper_bound(index);
				int right = *it;
				int deleted = query(left+1, right-1, tree);
				int interval = right-left-1-deleted;
				it = remainingTools.upper_bound(interval);
				if(it == remainingTools.begin()) {
					pos = false;
					break;
				}
				it--;
				// cout << interval << " used " << *it << endl;
				remainingTools.erase(it);
				update(index, tree, 1);
			}
			else {
				seen.insert(index);
			}
		}
		vector<int> realOrder;
		for(int i = 0; i < n; i++) {
			if(!del[nums[i]])
				realOrder.push_back(nums[i]);
		}
		if(realOrder != target)
			pos = false;
		
		if(pos)
			cout << "YES\n";
		else
			cout << "NO\n";
		
	}
}