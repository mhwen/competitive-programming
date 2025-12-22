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
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	map<ll, int> pre;
	ll s = 0;
	for(int i = 0; i < n; i++) {
		s += nums[i];
		pre[s] = i;
	}
	s = 0;
	map<ll, int> suf;
	for(int i = n-1; i >= 0; i--) {
		s += nums[i];
		suf[s] = i;
	}
	int cnt = 0;
	for(auto [amt, i] : pre) {
		if(suf.count(amt)) {
			if(suf[amt] > i+1)
				cnt+=2;
			else if(suf[amt] > i)
				cnt++;
		}
	}
	cout << max(0, n-1-cnt) << "\n";
}