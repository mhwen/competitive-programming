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
	int n;
	cin >> n;
	map<pair<int, int>, ll> ans;
	vector<priority_queue<pair<ll, int>>> f(n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			ll v;
			cin >> v;
			f[i].push({v, j});
			if(i != j)
				f[j].push({v, i});
		}
	}
	vector<ll> size(n, 1);
	vector<bool> out(n);
	for(int step = 0; step < n-1; step++) {
		ll largest = 0;
		int me = -1;
		for(int i = 0; i < n; i++) {
			if(out[i])
				continue;
			while(out[f[i].top().second])
				f[i].pop();
			if(f[i].top().first > largest) {
				largest = f[i].top().first;
				me = i;
			}
		}
		out[me] = true;
		f[me].pop();
		while(out[f[me].top().second])
			f[me].pop();
		int above = f[me].top().second;
		ll weight = (largest-f[me].top().first)/(n-size[me]);
		size[above]+=size[me];
		ans[{me, above}] = weight;
	}
	for(auto [e, w] : ans) {
		auto [a,b] = e;
		cout << a+1 << " " << b+1 << " " << w << "\n";
	}
}