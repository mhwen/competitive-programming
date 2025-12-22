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
	int n, k;
	cin >> n >> k;
	vector<int> m(n);
	for(int i = 0; i < n; i++)
		cin >> m[i];
	vector<int> c(k);
	for(int i = 0; i < k; i++)
		cin >> c[i];
	
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		return m[a] > m[b];
	});
	vector<vector<int>> ans;
	auto check = [&](int amt) {
		vector<vector<int>> hold(amt);
		for(int i = 0; i < n; i++) {
			int size = i/amt+1;
			int id = i%amt;
			hold[id].push_back(order[i]);
			if(c[m[order[i]]-1] < size)
				return false;
		}
		ans = hold;
		return true;
	};
	int l = 1, r = n;
	while(l <= r) {
		int mid = (l+r)/2;
		if(check(mid))
			r = mid-1;
		else
			l = mid+1;
	}
	cout << l << "\n";
	for(auto a : ans) {
		cout << sz(a) << " ";
		for(auto aa : a)
			cout << m[aa] << " ";
		cout << "\n";
	}
	cout << "\n";
}