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
		int n, m, q;
		cin >> n >> m >> q;
		vector<pair<int, int>> pos{{m, m}};
		for(int i = 0; i < q; i++) {
			int a;
			cin >> a;
			vector<pair<int, int>> newPos;
			for(auto [l, r] : pos) {
				if(l <= a && a <= r) {
					newPos.push_back({1, 1});
					newPos.push_back({n, n});
					if(l!=r)
						newPos.push_back({l, r});
				}
				else if(a < l)
					newPos.push_back({max(1, l-1), r});
				else
					newPos.push_back({l, min(n, r+1)});
			}
			pos.clear();
			sort(all(newPos));
			for(auto [l, r] : newPos) {
				if(pos.empty() || l > pos.back().second+1)
					pos.push_back({l, r});
				else
					pos.back().second = r;
			}
			int cnt = 0;
			for(auto [l, r] : pos)
				cnt += r-l+1;
			cout << cnt << " ";
		}
		cout << "\n";
	}
}