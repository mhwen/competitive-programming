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
		vector<int> score(n);
		int curr = 0;
		for(int i = 0; i < n-1; i++) {
			if(nums[i] < curr)
				curr--;
			else if(nums[i] > curr)
				curr++;
			score[i+1] = curr;
		}
		auto check = [&](int val) {
			int c = val;
			vector<int> need(n);
			need[n-1] = c;
			for(int i = n-1; i > 0; i--) {
				if(nums[i] >= c)
					c--;
				else
					c++;
				need[i-1] = min(need[i], c);
			}
			for(int i = 0; i < n; i++) {
				if(score[i] >= need[i])
					return true;
			}
			return false;
		};
		int l = 0, r = 2*n;
		while(l <= r) {
			int mid = (l+r)/2;
			if(check(mid))
				l = mid+1;
			else
				r = mid-1;
		}
		cout << r << "\n";
	}
}