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
	int n;
	cin >> n;
	map<int, set<int>> A;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		A[a].insert(i);
	}
	vector<pair<int, int>> events;
	for(int i = 0; i < n; i++) {
		int b;
		cin >> b;
		auto it = A[b].lower_bound(i);
		int r = -1, l = -1;
		if(it != A[b].end()) {
			r = *it-i;
			if(r == 0)
				l = 0;
			else {
				if(it == A[b].begin())
					l = i+n-*A[b].rbegin();
				else
					l = i-*prev(it);
			}
		}
		else {
			l = i-*prev(it);
			r = n-i+*A[b].begin();
		}
		events.push_back({l, r});
	}
	set<int> right;
	right.insert(0);
	sort(all(events));
	reverse(all(events));
	int best = n;
	for(auto [l, r] : events) {
		int s = min(l, *right.rbegin());
		best = min(best, l+*right.rbegin()+s);
		right.insert(r);
	}
	best = min(best, *right.rbegin());
	cout << best << "\n";
	
}