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


ll inversions(vector<int>& nums) {
	int n = sz(nums);
	vector<int> tree(2*n);
	ll count = 0;
	
	auto query = [&](int l, int r) {
		l += n; r += n;
		ll res = 0;
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
	};
	
	auto update = [&](int p) {
		p += n;
		while(p > 0) {
			tree[p]++;
			p >>= 1;
		}
	};
	
	for(int i : nums) {
		count += query(i+1, n-1);
		update(i);
	}
	return count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		vector<int> b(n);
		for(int i = 0; i < n; i++)
			cin >> b[i];
		auto aSorted = a;
		auto bSorted = b;
		sort(all(aSorted));
		sort(all(bSorted));
		if(aSorted != bSorted)
			cout << "NO\n";
		else {
			map<int, int> coords;
			for(int i = 0; i < n; i++)
				coords[aSorted[i]] = i;
			for(int i = 0; i < n; i++) {
				a[i] = coords[a[i]];
				b[i] = coords[b[i]];
			}
			ll aI = inversions(a);
			ll bI = inversions(b);
			if(abs(aI-bI)%2==0)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}