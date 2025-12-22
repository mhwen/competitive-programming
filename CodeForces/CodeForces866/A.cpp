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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		set<int> seen;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			seen.insert(nums[i]);
		}
		int mex = 0;
		while(seen.count(mex))
			mex++;
		if(mex == n)
			cout << "NO\n";
		else {
			if(seen.count(mex+1)) {
				int l = n, r = -1;
				for(int i = 0; i < n; i++) {
					if(nums[i] == mex+1) {
						l = min(l, i);
						r = max(r, i);
					}
				}
				set<int> newSeen;
				for(int i = 0; i < l; i++)
					newSeen.insert(nums[i]);
				for(int i = r+1; i < n; i++)
					newSeen.insert(nums[i]);
				int newMex = 0;
				while(newSeen.count(newMex))
					newMex++;
				if(newMex == mex)
					cout << "YES\n";
				else
					cout << "NO\n";
			}
			else
				cout << "YES\n";
		}
	}
}