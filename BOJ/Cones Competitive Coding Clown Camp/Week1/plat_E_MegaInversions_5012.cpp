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

void update(int p, vector<int>& tree) {
	int n = sz(tree)/2;
	p += n;
	while(p > 0) {
		tree[p]++;
		p >>= 1;
	}
}

int query(int l, int r, vector<int>& tree) {
	int n = sz(tree)/2;
	l += n; r += n;
	int res = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			res += tree[l];
			l++;
		}
		if(r%2==0) {
			res += tree[r];
			r--;
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		nums[i]--;
	}
	vector<int> tree(2*n);
	vector<ll> left(n);
	for(int i = 0; i < n-1; i++) {
		update(nums[i], tree);
		left[i+1] = query(nums[i+1]+1, n-1, tree);
	}
	fill(all(tree), 0);
	vector<ll> right(n);
	for(int i = n-1; i > 0; i--) {
		update(nums[i], tree);
		right[i-1] = query(0, nums[i-1]-1, tree);
	}
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ans += left[i]*right[i];
	}
	cout << ans << "\n";
}