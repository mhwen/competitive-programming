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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	vector<ll> preSum(n+1);
	for(int i = 0; i < n; i++) 
		preSum[i+1] = preSum[i]+nums[i];
	auto getSum = [&](int l, int r) {
		return preSum[r+1]-preSum[l];
	};
	
	vector<vector<ll>> tree(2*n);
	
	auto update = [&](int p, ll val) {
		p += n;
		while(p > 0) {
			tree[p].push_back(val);
			p /= 2;
		}
	};
	
	auto query = [&](int l, int r, ll val) {
		l += n; r += n;
		ll res = INF;
		for(; l <= r; l>>=1, r>>=1) {
			if(l%2==1) {
				auto it = upper_bound(all(tree[l]), val);
				if(it != tree[l].end())
					res = min(res, abs(*it-val));
				if(it != tree[l].begin())
					res = min(res, abs(*prev(it)-val));
				l++;
			}
			if(r%2==0) {
				auto it = upper_bound(all(tree[r]), val);
				if(it != tree[r].end())
					res = min(res, abs(*it-val));
				if(it != tree[r].begin())
					res = min(res, abs(*prev(it)-val));
				r--;
			}
		}
		return res;
	};
	
	
	for(int i = 0; i < n; i++)
		update(i, preSum[i+1]*2);
	
	for(int i = 0; i < 2*n; i++)
		sort(all(tree[i]));
	
	int q;
	cin >> q;
	while(q-->0) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		int third = (r-l+1)/3;
		ll left = getSum(l, l+third-1);
		ll mid = getSum(l+third, l+2*third-1);
		ll right = getSum(l+2*third, r);
		ll prefix = getSum(0, l+third-1);
		ll wanted = right-left+mid;
		ll ans = query(l+third-1, l+2*third-1, wanted+2*prefix);
		cout << ans << "\n";
	}
}