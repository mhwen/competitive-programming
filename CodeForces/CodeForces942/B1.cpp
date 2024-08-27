#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		//a > b
		//a == b(gcd(a, b)-1)
		//b divides a
		//a+b == k*b*b
		//a == k*b*b-b for some k
		//a == b(kb-1)
		
		//a < b
		//not possible
		ll ans = 0;
		for(ll i = 1; i <= m; i++) {
			ll range = n+i;
			ans += range/(i*i);
		}
		cout << ans-1 << "\n";
	}
}