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
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	vector<int> trees;
	for(int i = 0; i < n; i++) {
		if(s[i] == 'T')
			trees.push_back(i);
	}
	if(sz(trees) < k)
		cout << -1 << "\n";
	else {
		int best = n;
		for(int i = 0; i+k-1 < sz(trees); i++) {
			int l = trees[i];
			int r = trees[i+k-1];
			best = min(best, (r-l+1)/2);
		}
		cout << best << "\n";
	}
}