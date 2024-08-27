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
constexpr int INF = 1e9+5;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int& num : nums)
			cin >> num;
		
		vector<int> best(n+1, INF);
		best[0] = 0;
		vector<int> longest(n);
		int lis = 0;
		for(int i = 0; i < n; i++) {
			int pos = (int)(lower_bound(best.begin(), best.end(), nums[i])-best.begin());
			best[pos] = nums[i];
			longest[i] = pos;
			lis = max(lis, pos);
		}

		vector<int> ans;
		map<int, int> seen;
		seen[lis+1] = INF;
		for(int i = n-1; i >= 0; i--) {
			int nextLen = longest[i]+1;
			if(seen.count(nextLen) && nums[i] < seen[nextLen]) {
				if(!seen.count(longest[i]))
					seen[longest[i]] = nums[i];
				seen[longest[i]] = max(seen[longest[i]], nums[i]);
				ans.push_back(i+1);
			}
		}
		reverse(ans.begin(), ans.end());
		cout << sz(ans) << "\n";
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}