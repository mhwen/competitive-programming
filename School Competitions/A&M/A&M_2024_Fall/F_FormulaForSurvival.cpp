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

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> herb(n);
	vector<ll> ways(n+1);
	ways[0] = 1;
	for(int i = 0; i < n; i++) {
		cin >> herb[i];
		for(int j = n; j >= herb[i]; j--) {
			ways[j] += ways[j-herb[i]];
			ways[j] %= MOD;
		}
	}
	auto undo = [&](int val) {
		for(int i = val; i <= n; i++) {
			ways[i] -= ways[i-val];
			if(ways[i] < 0)
				ways[i] += MOD;
		}
	};
	while(m-->0) {
		int b, c;
		cin >> b >> c;
		while(c-->0) {
			int d;
			cin >> d;
			d--;
			undo(herb[d]);
		}
		if(ways[b])
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

}