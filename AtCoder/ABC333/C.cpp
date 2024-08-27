#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums;
	ll curr = 1;
	for(int i = 0; i < 12; i++) {
		nums.push_back(curr);
		curr = curr*10+1;
	}
	set<ll> pos;
	for(int i = 0; i < (int)nums.size(); i++) {
		for(int j = 0; j < (int)nums.size(); j++) {
			for(int k = 0; k < (int)nums.size(); k++) {
				pos.insert(nums[i]+nums[j]+nums[k]);
			}
		}
	}
	auto it = pos.begin();
	for(int i = 0; i < n-1; i++) {
		it++;
	}
	cout << *it << "\n";
}