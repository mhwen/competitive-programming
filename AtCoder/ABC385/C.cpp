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
	int n;
	cin >> n;
	vector<int> h(n);
	for(int i = 0; i < n; i++)
		cin >> h[i];
	int best = 1;
	for(int i = 0; i < n; i++) {
		for(int add = 1; add < n; add++) {
			int curr = h[i];
			int amt = 0;
			for(int j = i; j < n; j+=add) {
				if(h[j] != curr) {
					curr = h[j];
					amt = 1;
				}
				else
					amt++;
				best = max(best, amt);
			}
		}
	}
	cout << best << "\n";
}