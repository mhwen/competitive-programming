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
		int n, m, q;
		cin >> n >> m >> q;
		set<int> teach;
		for(int i = 0; i < m; i++) {
			int b;
			cin >> b;
			teach.insert(b);
		}
		while(q-->0) {
			int a;
			cin >> a;
			auto right = teach.lower_bound(a);
			//no guy on right
			if(right == teach.end()) {
				int left = *prev(right);
				cout << n-left << "\n";
			}
			//guy on me
			else if(*right == a) {
				cout << 0 << "\n";
			}
			else {
				//no guy on left
				if(right == teach.begin()) {
					cout << *right-1 << "\n";
				}
				else {
					int left = *prev(right);
					int len = *right-left;
					cout << len/2 << "\n";
				}
			}
		}
	}
}