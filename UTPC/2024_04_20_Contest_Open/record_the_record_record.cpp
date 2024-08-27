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
	set<int> seen;
	int best = 0;
	for(int i = 0; i < n; i++) {
		int m;
		cin >> m;
		int before = (int)seen.size();
		for(int j = 0; j < m; j++) {
			int a;
			cin >> a;
			seen.insert(a);
		}
		best = max(best, (int)seen.size()-before);
	}
	cout << best << "\n";
}