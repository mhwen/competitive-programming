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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll INF = 1e9+5;

set<int> check(vector<int> nums) {
	bool found = false;
	int n = sz(nums);
	do {
		found = false;
		for(int i = 0; i < n; i++) {
			int nxt = (i+1)%n;
			int old = nums[nxt];
			nums[nxt] = max(0, nums[nxt]-nums[i]);
			if(nums[nxt] != old)
				found = true;
		}
	} while(found);
	set<int> res;
	for(int i = 0; i < n; i++)
		if(nums[i] > 0)
			res.insert(i);
	return res;
}

set<int> solve(vector<int> nums) {
	int n = sz(nums);
	int start = -1;
	while(true) {
		for(int i = 0; i < n; i++) {
			if(nums[i] == 0) {
				start = i;
				goto go;
			}
			int nxt = (i+1)%n;
			nums[nxt] = max(0, nums[nxt]-nums[i]);
		}
	}
	go:
	set<int> ans;
	if(start != -1) {
		int curr = start;
		vector<pair<ll, ll>> prev;
		ll prevSum = 0;
		while((curr+1)%n != start) {
			// cout << "at " << curr << " with val " << nums[curr] << " prevSum:" << prevSum << endl;
			// cout << "val next "<< nums[(curr+1)%n] << endl;
			// cout << "Prev: " << endl;
			// for(auto [a,b]:prev)
				// cout << a << " " << b << endl;
			int nxt = (curr+1)%n;
			vector<pair<ll, ll>> newPrev;
			ll sum = 0;
			if(nums[nxt] > 0) {
				int id = 0;
				while(sum < INF && id < sz(prev) && nums[nxt] > 0) {
					if(prev[id].second == 0) {
						id++;
						continue;
					}
					nums[nxt] = (int)max(0LL, nums[nxt]-prev[id].first);
					sum += nums[nxt];
					prevSum -= prev[id].first;
					if(nums[nxt] > 0)
						newPrev.emplace_back(nums[nxt], 1);
					prev[id].second--;
				}
				if(prevSum >= nums[nxt])
					nums[nxt] = 0;
				if(nums[nxt] > 0) {
					newPrev.emplace_back(nums[nxt], INF);
					ans.insert(nxt);
					sum = INF;
				}
			}
			prevSum = sum;
			prev = newPrev;
			curr = nxt;
		}
	}
	return ans;
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
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		auto ans = solve(nums);
		// auto brute = check(nums);
		// if(ans != brute) {
			// cout << "BAD\n";
			// for(int i : nums)
				// cout << i << " ";
			// cout << endl;
			// for(int i : brute)
				// cout << i+1 << " ";
			// cout << "\n";
			// for(int i : ans)
				// cout << i+1 << " ";
			// cout << "\n";
		// }
		cout << sz(ans) << "\n";
		for(int i : ans)
			cout << i+1 << " ";
		cout << "\n";
	}
}