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
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		map<int, int> freq;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			freq[a]++;
		}
		vector<int> cnts;
		for(auto [a, cnt] : freq)
			cnts.push_back(cnt);
		sort(all(cnts));
		int i = 0;
		int tot = 0;
		while(i < sz(cnts) && tot+cnts[i] <= k)
			tot += cnts[i++];
		cout << max(1, sz(cnts)-i) << "\n";
	}
}