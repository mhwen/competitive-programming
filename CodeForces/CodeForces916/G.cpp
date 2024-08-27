#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <stack>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

pair<ll, set<int>*> merge(pair<ll, set<int>*> a, pair<ll, set<int>*> b) {
	if(a.second->size() < b.second->size())
		swap(a, b);
	a.first += b.first;
	for(int val : *b.second)
		a.second->insert(val);
	return a;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		stack<pair<ll, set<int>*>> s;
		vector<bool> seen(n+1);
		for(int i = 0; i < 2*n; i++) {
			int c;
			cin >> c;
			if(!seen[c]) {
				set<int>* hold = new set<int>{c};
				s.push({1, hold});
				seen[c] = true;
			}
			else {
				set<int>* empty = new set<int>{};
				pair<ll, set<int>*> merged{0, empty};
				while(s.top().second->count(c)==0) {
					if(s.top().second->size() > 0)
						merged = merge(merged, s.top());
					s.pop();
				}
				merged = merge(merged, s.top());
				s.pop();
				merged.second->erase(c);
				s.push(merged);
			}
		}
		int min = 0;
		ll ways = 1;
		while(!s.empty()) {
			min++;
			ways = ways*2%MOD*s.top().first%MOD;
			s.pop();
		}
		cout << min << " " << ways << "\n";
	}
}