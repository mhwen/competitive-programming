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

void solve(int n, int needed) {
	vector<pair<int, int>> ans;
	map<int, int> deps;
	deps[0] = 0;
	int currDep = 0;
	for(int i = 1; i < n; i++) {
		int rem = n-i-1;
		int take = currDep+1;
		if(needed-take > rem) {
			ans.push_back({deps[currDep], i});
			currDep++;
			deps[currDep] = i;
			needed -= take;
		}
		else {
			take = needed-rem;
			ans.push_back({deps[take-1], i});
			needed -= take;
		}
	}
	cout << n << " " << sz(ans) << "\n";
	for(auto [x, y] : ans)
		cout << x+1 << " " << y+1 << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string line;
	cin >> line;
	int idx = (int)line.find('/');
	int a = stoi(line.substr(0, idx));
	int b = stoi(line.substr(idx+1, line.size() - idx - 1));
	for(int n = b; n <= 1000000; n+=b) {
		if(n-1 <= n/b*a && n/b*a <= (n-1)*n/2) {
			solve(n, n*a/b);
			return 0;
		}
	}
	cout << "impossible\n";
}