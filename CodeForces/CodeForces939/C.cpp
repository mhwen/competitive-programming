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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> o(n);
		iota(all(o), 1);
		reverse(all(o));
		ll tot = 0;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < n; c++) {
				tot += n-min(r,c);
			}
		}
		cout << tot << " " << 2*n << "\n";
		for(int i = 0; i < 2*n; i++) {
			cout << i%2+1 << " " << i/2+1;
			for(int a : o)
				cout << " " << a;
			cout << "\n";
		}	
	}
}