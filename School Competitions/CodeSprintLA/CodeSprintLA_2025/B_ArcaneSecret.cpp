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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	int size = n/k;
	map<int, int> f;
	for(int i = 0; i < n; i++) {
	    int a;
	    cin >> a;
	    f[a]++;
	}
	int below = 0;
	int ans = 0;
	for(auto [v, cnt] : f) {
	    int above = n-cnt-below;
	    if(below+cnt >= (k/2+1)*size && above+cnt-1 >= k/2)
	        ans += cnt;
	    below += cnt;
	}
	cout << ans << "\n";
}