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
		int n;
		ll k;
		cin >> n >> k;
		vector<ll> a(n);
		vector<ll> b(n);
		for(int i = 0; i < n; i++)
			cin >> a[i] >> b[i];
		if(k > a[0]+b[0]) {
			cout << "NO\n";
			continue;
		}
		if(a[0] >= k) {
			cout << "YES\n";
			continue;
		}
		multiset<ll> remA;
		priority_queue<pair<ll, int>> q;
		priority_queue<pair<ll, ll>> usable;
		for(int i = 1; i < n; i++) {
			remA.insert(a[i]);
			q.push({a[i]+b[i], i});
		}
		ll need = k-b[0];
		bool work = false;
		bool win = false;
		do {
			if(!remA.empty() && *remA.rbegin() >= need) {
				win = true;
				break;
			}
			work = false;
			while(!q.empty() && q.top().first >= need) {
				int id = q.top().second;
				usable.push({-a[id], b[id]});
				q.pop();
				work = true;
			}
			if(!usable.empty()) {
				auto [A, B] = usable.top();
				need -= B;
				remA.erase(remA.find(-A));
				usable.pop();
				work = true;
			}
		} while(work);
		
		if(win)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}