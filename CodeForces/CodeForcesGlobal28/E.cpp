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
		int n, m;
		cin >> n >> m;
		if(m >= 2*n) {
			cout << "NO\n";
			continue;
		}
		vector ans(2*n, vector<int>(2*n-1));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 2*n-1; j++) {
				ans[(2*i+j)%(2*n)][j] = i+1;
				ans[(2*i+j+1)%(2*n)][j] = i+1;
			}
		}
		cout << "YES\n";
		for(auto v : ans) {
			for(int i = 0; i < m; i++)
				cout << v[i] << " ";
			cout << "\n";
		}
	}
}