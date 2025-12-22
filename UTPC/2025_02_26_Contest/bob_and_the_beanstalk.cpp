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
	int rem = 0;
	for(int i = 1; i <= n; i++) {
	    int amt;
	    cin >> amt;
	    rem += amt;
	    rem -= min(rem, k);
	}
	int extra = 0;
	while(rem > 0) {
	    extra++;
	    rem -= k;
	}
	cout << n+extra << "\n";
}