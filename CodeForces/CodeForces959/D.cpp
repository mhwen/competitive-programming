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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		vector<pair<int, int>> ans(n-1);
		vector<int> rem(n);
		iota(all(rem), 0);
		for(int i = n-1; i >= 1; i--) {
			vector<vector<int>> pool(i);
			for(int j : rem)
				pool[a[j]%i].push_back(j);
			int toDelete = -1;
			for(int val = 0; val < i; val++) {
				if(sz(pool[val]) > 1) {
					ans[i-1] = {pool[val].front()+1, pool[val].back()+1};
					toDelete = pool[val].back();
					break;
				}
			}
			rem.erase(find(all(rem), toDelete));
		}
		cout << "YES\n";
		for(auto [A,B] : ans)
			cout << A << " " << B << "\n";
	}
}