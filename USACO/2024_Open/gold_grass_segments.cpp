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

int query(int l, int r, vector<int>& tree) {
	int n = sz(tree)/2;
	l+=n; r+=n;
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

void update(int p, vector<int>& tree) {
	int n = sz(tree)/2;
	p+=n;
	while(p > 0) {
		tree[p]++;
		p>>=1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> seen;
	vector<pair<pair<int, int>, int>> grass(n+1);
	vector<pair<int, int>> events;
	for(int i = 1; i <= n; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		seen.push_back(l);
		seen.push_back(r);
		seen.push_back(l+k-1);
		seen.push_back(r-k+1);
		grass[i] = {{l, r}, k};
		events.push_back({r-l, -i});
		events.push_back({k, i});
	}
	
	sort(all(seen));
	seen.resize(unique(all(seen))-seen.begin());
	auto compress = [&](int val) {
		return (int)(lower_bound(all(seen), val) - seen.begin());
	};
	
	vector<int> starts(2*sz(seen));
	vector<int> ends(2*sz(seen));
	
	//-i -> add segment
	// i -> query segment
	sort(all(events), [&](auto a, auto b) { 
		if(a.first != b.first) {
			return a.first > b.first;
		}
		else {
			return a.second < b.second;
		}
	});
	
	vector<int> ans(n+1);
	
	int active = 0;
	
	for(auto [e, id] : events) {
		if(id < 0) {
			id = abs(id);
			auto [l, r] = grass[id].first;
			l = compress(l);
			r = compress(r);
			update(l, starts);
			update(r, ends);
			active++;
		}
		else {
			auto [l, r] = grass[id].first;
			int k = grass[id].second;
			int low_b = compress(l+k-1);
			int high_b = compress(r-k+1);
			ans[id] = active-query(0, low_b, ends)-query(high_b, sz(seen)-1, starts);
		}
	}
	
	for(int i = 1; i <= n; i++)
		cout << ans[i]-1 << "\n";
}