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
	int n, m;
	cin >> n >> m;
	vector<int> counts(m);
	for(int i = 0; i < n; i++) {
		int flavor;
		cin >> flavor;
		counts[flavor-1]++;
	}
	for(int c : counts)
		cout << (c+11)/12 << "\n";
}