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
	int T;
	cin >> T;
	for(int ca = 1; ca <= T; ca++) {
		int n, k;
		ll b, t;
		cin >> n >> k >> b >> t;
		vector<ll> x(n);
		for(int i = 0; i < n; i++)
			cin >> x[i];
		vector<ll> v(n);
		for(int i = 0; i < n; i++)
			cin >> v[i];
			
		auto reaches = [&](int i) {
			return v[i]*t+x[i] >= b;
		};
		
		ll ans = 0;
		int bad = 0;
		int got = 0;
		for(int i = n-1; i >= 0; i--) {
			if(got == k)
				break;
			if(reaches(i)) {
				ans += bad;
				got++;
			}
			else
				bad++;
		}
		cout << "Case #" << ca << ": ";
		if(got == k)
			cout << ans << "\n";
		else
			cout << "IMPOSSIBLE\n";
	}
}