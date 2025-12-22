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
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
	    cin >> a[i];
	vector<pair<int, int>> best(n+1);
	for(int i = n-1; i >= 0; i--) {
	    best[i] = {a[i], -1};
	    if(i+k <= n-1)
	        best[i] = max(best[i], {best[i+k].first, best[i+k].second-k});
	}
	
	int i = 0;
	while(i < n) {
	    cout << best[i].first << " ";
	    i -= best[i].second;
	}
	cout << "\n";
}