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
	int a, b, c, x, y;
	cin >> a >> b >> c >> x >> y;
	if(x > y) {
	    swap(x, y);
	    swap(a, b);
	}
	int ans = 0;
	while(c >= x && a > 0) {
	    ans++;
	    c -= x;
	    a--;
	}
	while(c >= y && b > 0) {
	    ans++;
	    c -= y;
	    b--;
	}
	cout << ans << "\n";
}