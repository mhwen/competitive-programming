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
		vector<int> a(n);
		vector<vector<int>> seen(n+1);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			seen[a[i]].push_back(i);
		}
		int l = 0, r = n-1;
		int lo = n-1, hi = 0;
		bool bad = false;
		for(int i = 1; i <= n; i++) {
			auto& v = seen[i];
			if(v.empty())
				continue;
			sort(all(v));
			lo = min(lo, v.front());
			hi = max(hi, v.back());
			if(hi-lo+1 > i)
				bad = true;
			l = max(l, hi-i+1);
			r = min(r, lo+i-1);
		}
		if(bad)
			r = -1;
		cout << max(0, r-l+1) << "\n";
	}
}