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
#include <fstream>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

struct Node {
	ll cost;
	map<int, int> taken;
	int index;
	Node(ll c) : cost(c), taken(), index(0) {}
	bool operator< (const Node& a) const { return cost < a.cost; }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("roboherd.in");
	ofstream cout("roboherd.out");
	int n, k;
	cin >> n >> k;
	ll ans = 0;
	vector<pair<ll, pair<int, int>>> next;
	for(int i = 0; i < n; i++) {
		int m;
		cin >> m;
		vector<ll> vals(m);
		for(int j = 0; j < m; j++)
			cin >> vals[j];
		sort(all(vals));
		ans += vals[0]*k;
		for(int j = 1; j < m; j++) {
			next.push_back({vals[j]-vals[0], {i, j}});
		}
	}
		
	sort(all(next));

	auto toNextIndex = [&](Node& curr) {
		while(curr.index < sz(next) && curr.taken.count(next[curr.index].second.first))
			curr.index++;
	};

	set<map<int, int>> seen;
	priority_queue<pair<ll, Node>> q;
	q.push({-next[0].first, Node(0)});
	k--;
	while(k > 0) {
		assert(!q.empty());
		auto p = q.top();
		q.pop();
		ll price = -p.first;
		Node curr = p.second;
		map<int, int> newTaken = curr.taken;
		newTaken[next[curr.index].second.first] = next[curr.index].second.second;
		if(seen.count(newTaken) == 0) {
			k--;
			seen.insert(newTaken);
			Node newNode = Node(price);
			newNode.taken = newTaken;
			ans += price;
			toNextIndex(newNode);
			if(newNode.index < sz(next)) {
				q.push({-newNode.cost-next[newNode.index].first, newNode});
			}
		}
		curr.index++;
		toNextIndex(curr);
		if(curr.index < sz(next)) {
			q.push({-curr.cost-next[curr.index].first, curr});
		}
	}
	cout << ans << "\n";
}