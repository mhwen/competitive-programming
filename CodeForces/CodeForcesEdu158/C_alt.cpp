#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

vector<ll> solve1(vector<ll> nums) {
	int n = (int)nums.size();
	int moves = 0;
	ll add = 0;
	for(int bit = 30; bit >= 0; bit--) {
		bool allSame = true;
		for(int i = 1; i < n; i++) {
			if((nums[i]&(1<<bit)) != (nums[0]&(1<<bit))) {
				allSame = false;
				break;
			}
		}
		if(!allSame) {
			ll largest = 0;
			ll smallest = (1<<bit)-1;
			for(int i = 0; i < n; i++) {
				if(nums[i]&(1<<bit)) {
					largest = max(largest, nums[i]&((1<<bit)-1));
				}
				else {
					smallest = min(smallest, nums[i]&((1<<bit)-1));
				}
			}
			if(largest < smallest) {
				add = (1<<bit)-smallest;
				moves = bit;
			}
			else {
				moves = bit+1;
			}
			break;
		}
	}
	vector<ll> ans;
	if(0 < moves) {
		ans.push_back(add);
		for(int i = 0; i < n; i++) {
			nums[i] = (nums[i]+add)/2;
		}
		while(true) {
			bool good = true;
			for(int i = 0; i < n; i++) {
				if(nums[0] != nums[i]) {
					good = false;
					break;
				}
			}
			if(good)
				break;
			ans.push_back(0);
			for(int i = 0; i < n; i++) {
				nums[i] = nums[i]/2;
			}
		}
	}
	return ans;
}

vector<ll> solve2(vector<ll> nums) {
	ll mx = 0;
	ll mn = 1e9;
	int n = (int)nums.size();
	for(int i = 0; i < n; i++) {
		mx = max(mx, nums[i]);
		mn = min(mn, nums[i]);
	}
	vector<ll> moves;
	while(mn < mx) {
		if(mn%2==1 && mx%2==0) {
			moves.push_back(1);
			mn = (mn+1)/2;
			mx = (mx+1)/2;
		}
		else {
			moves.push_back(0);
			mn = mn/2;
			mx = mx/2;
		}
	}
	return moves;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		auto res = solve1(nums);
		cout << res.size() << "\n";
		if(0 < (int)res.size() && (int)res.size() <= n) {
			for(ll l : res)
				cout << l << " ";
			cout << "\n";
		}
	}

}