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
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> par(n+m);
	vector<int> sizes(n+m, 1);
	iota(all(par), 0);
	int components = n+m;
	
	function<int(int)> getPar = [&](int a) {
		if(par[a] == a)
			return a;
		return par[a] = getPar(par[a]);
	};
	
	auto merge = [&](int a, int b) {
		a = getPar(a);
		b = getPar(b);
		if(a == b)
			return;
		components--;
		if(sizes[a] < sizes[b])
			swap(a, b);
		par[b] = a;
		sizes[a] += sizes[b];
	};
	
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		b += n;
		merge(a, b);
	}
	cout << components-1 << "\n";
}