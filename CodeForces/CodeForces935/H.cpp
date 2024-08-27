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
	int t;
	cin >> t;
	vector<int> counts(1e6);
	while(t-->0) {
		int n, x;
		cin >> n >> x;
		vector<int> nums(n);
		vector<int> zeroCount(20);
		vector<bool> relevant(20, true);
		int maxSeen = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			counts[nums[i]]++;
			maxSeen = max(maxSeen, nums[i]);
			for(int bit = 0; bit < 20; bit++) {
				if(((1<<bit)&nums[i]) == 0) {
					zeroCount[bit]++;
					if(zeroCount[bit] > 2)
						relevant[bit] = false;
				}
			}
		}
		
		bool found = false;
		pair<int, int> mine;
		
		auto compute = [&](const vector<int>& a, const vector<int>& b) {
			int ans = 0;
			for(int bit = 0; bit < 20; bit++) {
				int zeros = zeroCount[bit]-a[bit]-b[bit];
				if(zeros == 0)
					ans += (1<<bit);
			}
			return ans;
		};
		
		for(int gcd = 1; gcd <= maxSeen; gcd++) {
			map<vector<int>, int> seen;
			for(int val = gcd; val <= maxSeen; val+=gcd) {
				if(counts[val] > 0) {
					vector<int> mask(20);
					for(int bit = 0; bit < 20; bit++) {
						if(((1<<bit)&val) == 0 && relevant[bit]) {
							mask[bit] = 1;
						}
					}
					for(auto prev : seen) {
						int andVal = compute(prev.first, mask);
						if(gcd > andVal+x) {
							found = true;
							mine = {val, prev.second};
							goto A;
						}
					}
					seen[mask] = val;
					if(counts[val] > 1) {
						int andVal = compute(mask, mask);
						if(gcd > andVal+x) {
							found = true;
							mine = {val, val};
							goto A;
						}
					}
				}
				

			}
		}
		A:
		
		if(found) {
			cout << "YES\n";
			cout << 2 << " " << mine.first << " " << mine.second << "\n";
			cout << n-2;
			for(int i : nums) {
				if(i == mine.first)
					mine.first = -1;
				else if(i == mine.second)
					mine.second = -1;
				else
					cout << " " << i;
			}
			cout << "\n";
			
		}
		else {
			cout << "NO\n";
		}
		
		for(int i = 0; i < n; i++) {
			counts[nums[i]]--;
		}
		
		
	}
}