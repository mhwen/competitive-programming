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
	int n, q;
	cin >> n >> q;
	int latest = n;
	vector<int> counts(n);
	for(int i = 0; i < n; i++) {
		int pos;
		cin >> pos;
		int a = pos;
		int b = n-pos;
		if(a > b)
			swap(a, b);
		counts[a]++;
		latest = min(latest, b);
	}
	for(int i = 1; i < n; i++)
		counts[i] += counts[i-1];
	while(q-->0) {
		int val;
		cin >> val;
		if(val >= latest)
			cout << -1 << "\n";
		else
			cout << counts[val] << "\n";
	}
}