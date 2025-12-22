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

typedef pair<pair<int, int>, pair<int, int>> info;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		map<ll, vector<int>> m;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			m[-nums[i]].push_back(i);
		}
		
		ll curr = 0;
		//0 is no lose, 1 is lose 1, 2 is unusable
		vector<int> types(3);
		
		auto classify = [&](info a) {
			if(a.second.first+a.second.second==0)
				return 2;
			int len = a.first.second-a.first.first+1;
			if(len%2==0)
				return 0;
			else {
				int parity = a.first.first;
				if(parity%2==0 && a.second.first)
					return 0;
				if(parity%2==1 && a.second.second)
					return 0;
				return 1;
			}
		};
		
		auto score = [&](info a) {
			int len = a.first.second-a.first.first+1;
			return (len+1)/2;
		};
		
		auto merge = [&](info a, info b) {
			if(a > b)
				swap(a, b);
			types[classify(a)]--;
			types[classify(b)]--;
			curr -= score(a);
			curr -= score(b);
			info res = {{a.first.first, b.first.second}, {a.second.first|b.second.first, a.second.second|b.second.second}};
			curr += score(res);
			types[classify(res)]++;
			return res;
		};
		set<info> active;
		ll best = 0;
		ll mx = *max_element(all(nums));
		
		auto insert = [&](int a, bool big) {
			
			info me = {{a, a}, {0, 0}};
			if(big) {
				me.second.first = a%2==0;
				me.second.second = a%2==1;
			}
			auto it = active.lower_bound(me);
			curr++;
			types[classify(me)]++;
			
			if(it != active.end()) {
				auto right = *it;
				if(right.first.first == me.first.second+1) {
					me = merge(me, right);
					active.erase(right);
				}
			}
			it = active.lower_bound(me);
			if(it != active.begin()) {
				it = prev(it);
				auto left = *it;
				if(left.first.second+1 == me.first.first) {
					me = merge(left, me);
					active.erase(left);
				}
			}
			active.insert(me);
		};
		
		for(auto& [val, ids] : m) {
			for(int i : ids) {
				insert(i, -val==mx);
			}
			ll fix = 0;
			if(types[0] == 0)
				fix = -1;
			best = max(best, mx-val+curr+fix);
		}
		cout << best << "\n";
	}
}