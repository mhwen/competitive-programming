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
		ll n, b, c;
		cin >> n >> b >> c;
		if(b == 0) {
			if(c < n-2)
				cout << -1 << "\n";
			else if(c == n-2 || c == n-1)
				cout << n-1 << "\n";
			else
				cout << n << "\n";
		}
		else {
			if(c >= n)
				cout << n << "\n";
			else
				cout << n-((n-1-c)/b+1) << "\n";
		}
	}
}