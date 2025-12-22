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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	map<int, int> cnt;
	for(int i = 0; i < 50*n; i++) {
		int num;
		cin >> num;
		cnt[num]++;
	}
	vector<int> ans;
	for(auto [a, c] : cnt) {
		if(c > 2*n)
			ans.push_back(a);
	}
	if(sz(ans) == 0)
		cout << -1 << "\n";
	else {
		for(int a : ans)
			cout << a << " ";
	}
}