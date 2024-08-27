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
		vector<ll> big(n+1);
		vector<ll> small(n+1);
		for(int i = 0; i < n; i++) {
			small[i+1] = min(small[i]+nums[i], abs(small[i]+nums[i]));
			big[i+1] = max(big[i]+nums[i], abs(big[i]+nums[i]));
			big[i+1] = max(big[i+1], abs(small[i+1]));
		}
		cout << big[n] << "\n";
	}
}