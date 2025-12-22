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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		int ans = 0;
		for(int i = 0; i < k; i++) {
			int a, b;
			cin >> a >> b;
			int d = abs(a-b);
			if(d%2==0)
				ans++;
		}
		cout << ans << "\n";
	}
}