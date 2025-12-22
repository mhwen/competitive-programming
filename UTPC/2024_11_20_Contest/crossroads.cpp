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
	if(n == 1) {
		cout << 0 << "\n";
		return 0;
	}
	if(n == 2) {
		cout << 1 << "\n";
		cout << 1 << "\n";
		cout << 1 << " " << 2 << "\n";
		return 0;
	}
	vector<vector<pair<int, int>>> ans;
	auto M = [&](int i) {
		return (i+n)%n+1;
	};
	auto output = [&](int a, int b) {
		vector<pair<int, int>> res;
		set<int> seen;
		for(int i = -n/2; i <= n/2; i++) {
			int A = M(a-i);
			int B = M(b+i);
			if(A == B)
				continue;
			if(seen.count(A) || seen.count(B))
				continue;
			seen.insert(A);
			seen.insert(B);
			res.emplace_back(A, B);
		}
		if(sz(res))
			ans.push_back(res);
	};
	if(n%2==0) {
		for(int d = 0; d <= 1; d++)
			for(int i = 0; i < n/2; i++)
				output(i, i+n/2+d);
	}
	else {
		for(int i = 0; i < n; i++)
			output(i, i+n/2);
	}
	assert(sz(ans) == n);
	cout << sz(ans) << "\n";
	for(auto& v : ans) {
		cout << sz(v) << "\n";
		for(auto [a,b] : v)
			cout << a << " " << b << "\n";
	}
}