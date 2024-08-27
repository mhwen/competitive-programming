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

vector<ll> coefficients(ll l) {
	vector<ll> c;
	for(ll i = 0; i < l; i++) {
		ll val = (l-i)*i;
		if(val <= 200000)
			c.push_back(val);
	}
	return c;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; ll l;
	cin >> n >> l;
	auto edges = coefficients(l);
	vector<int> dist(2e5+5, -1);
	queue<pair<ll, int>> q;
	q.push({0, 0});
	while(!q.empty()) {
		auto curr = q.front();
		ll num = curr.first;
		int d = curr.second;
		q.pop();
		if(dist[num] != -1)
			continue;
		dist[num] = d;
		for(ll add : edges) {
			if(num+add < sz(dist) && dist[num+add] == -1)
				q.push({num+add, d+1});
		}
	}
	
	while(n-->0) {
		ll a;
		cin >> a;
		cout << dist[a] << "\n";
	}
}