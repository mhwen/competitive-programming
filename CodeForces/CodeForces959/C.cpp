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
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n, x;
		cin >> n >> x;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		vector<ll> ways(n+1);
		int right = 0;
		ll sum = 0;
		for(int left = 0; left < n; left++) {
			if(left > 0)
				sum -= nums[left-1];
			while(right < n && sum <= x) {
				sum += nums[right];
				right++;
			}
			if(sum > x) {
				ways[right] += ways[left]+1;
			}
		}
		cout << n*(n+1)/2-accumulate(all(ways), 0LL) << "\n";
	}
}