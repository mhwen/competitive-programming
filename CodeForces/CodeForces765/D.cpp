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
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	if(k == 0) {
		cout << n << "\n";
		for(int i = 1; i <= n; i++)
			cout << i << " ";
		cout << "\n";
		return 0;
	}
	
	k--;
	int bit = 0;
	while((1<<bit) <= k)
		bit++;
	map<int, vector<int>> buckets;
	for(int i = 0; i < n; i++)
		buckets[a[i]>>bit].push_back(i);

	vector<int> ans;
	for(auto& [_, v] : buckets) {
		bool found = false;
		for(int b = 0; b < bit; b++) {
			if(k&(1<<b))
				continue;
			map<int, int> seen;
			for(auto id : v) {
				int val = a[id];
				val %= (1<<bit);
				seen[val>>b] = id;
			}
			for(auto id : v) {
				int val = a[id];
				val %= (1<<bit);
				int needed = (k>>b)^(val>>b)^1;
				if(seen.count(needed)) {
					ans.push_back(id);
					ans.push_back(seen[needed]);
					found = true;
					break;
				}
			}
			if(found)
				break;
		}
		if(!found)
			ans.push_back(v.front());
	}
	if(sz(ans) > 1) {
		cout << sz(ans) << "\n";
		for(auto val : ans)
			cout << val+1 << " ";
		cout << "\n";
	}
	else
		cout << -1 << "\n";
}