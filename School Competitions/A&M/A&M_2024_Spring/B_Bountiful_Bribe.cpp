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
	priority_queue<pair<ll, pair<string, ll>>> toppings;
	for(int i = 0; i < n; i++) {
		string s;
		ll h, a;
		cin >> s >> h >> a;
		toppings.push({h, {s, a}});
	}
	for(int i = 0; i < 8; i++) {
		auto curr = toppings.top();
		toppings.pop();
		cout << curr.second.first << "\n";
		curr.second.second--;
		if(curr.second.second > 0) {
			toppings.push(curr);
		}
	}
}