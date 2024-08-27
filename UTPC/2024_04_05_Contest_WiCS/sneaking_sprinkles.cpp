#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	priority_queue<ll> q;
	for(int i = 0; i < n; i++) {
		ll delta;
		cin >> delta;
		q.push(delta);
	}
	
	ll added = 0;
	for(int i = 0; i < n; i++) {
		ll val;
		cin >> val;
		added += val;
		ll delta = q.top();
		q.pop();
		ll amt = delta+added;
		ll take = amt/2;
		q.push(delta-take);
	}
	ll ans = added*n;
	while(!q.empty()) {
		ans += q.top();
		q.pop();
	}
	cout << ans << "\n";
}