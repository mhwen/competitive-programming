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
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		bool found = false;
		for(int i = 0; i < n-1; i++) {
			if(nums[i]*2 > nums[i+1] && nums[i+1]*2 > nums[i])
				found = true;
		}
		if(found)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}