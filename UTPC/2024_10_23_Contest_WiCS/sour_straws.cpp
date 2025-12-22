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
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sort(all(nums));
	vector<int> best(n, 1);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < i; j++) {
			if(nums[i]%nums[j]==0)
				best[i] = max(best[i], best[j]+1);
		}
	}
	cout << *max_element(all(best)) << "\n";
}